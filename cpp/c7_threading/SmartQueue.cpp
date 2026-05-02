#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>
#include <optional>

template<typename T>
class SmartQueue {
private:
    std::queue<T> queue_;
    mutable std::mutex mtx_;    // used by unique_lock
    std::condition_variable cv_; //wait, wait_for(time_out), notify_one, notify_all
    size_t max_size_;
    bool closed_ = false;

public:
    explicit SmartQueue(size_t max_size = SIZE_MAX) : max_size_(max_size) {}
    
    // Disable copy constructor and assignment operator for thread safety
    SmartQueue(const SmartQueue&) = delete;
    SmartQueue& operator=(const SmartQueue&) = delete;
    
    // Push an item to the queue (blocks if full)
    void push(const T& item) {
        std::unique_lock<std::mutex> lock(mtx_);
        
        // Wait until queue has space or is closed
        // The condition lambda is only evaluated in these specific cases:
        //  - Initially - when wait() is first called
        //  - After being notified - when another thread calls notify_one() or notify_all()
        cv_.wait(lock, [this] { return queue_.size() < max_size_ || closed_; });
        
        if (closed_) {
            throw std::runtime_error("Cannot push to closed queue");
        }
        
        queue_.push(item);
        cv_.notify_one(); // Notify waiting consumers
    }
    
    // Push with move semantics
    void push(T&& item) {
        std::unique_lock<std::mutex> lock(mtx_);
        
        cv_.wait(lock, [this] { return queue_.size() < max_size_ || closed_; });
        
        if (closed_) {
            throw std::runtime_error("Cannot push to closed queue");
        }
        
        queue_.push(std::move(item));
        cv_.notify_one();
    }
    
    // Push with timeout (returns false if timeout)
    template<typename Rep, typename Period>
    bool push_for(const T& item, const std::chrono::duration<Rep, Period>& timeout) {
        std::unique_lock<std::mutex> lock(mtx_);
        
        if (!cv_.wait_for(lock, timeout, [this] { return queue_.size() < max_size_ || closed_; })) {
            return false; // Timeout
        }
        
        if (closed_) {
            throw std::runtime_error("Cannot push to closed queue");
        }
        
        queue_.push(item);
        cv_.notify_one();
        return true;
    }
    
    // Pop an item from the queue (blocks if empty)
    T pop() {
        std::unique_lock<std::mutex> lock(mtx_);
        
        // Wait until queue has items or is closed
        cv_.wait(lock, [this] { return !queue_.empty() || closed_; });
        
        if (queue_.empty() && closed_) {
            throw std::runtime_error("Cannot pop from empty closed queue");
        }
        
        // Without move (copy)
        // T item = queue_.front(); // ❌ Creates a copy of the object (inefficient) 
        T item = std::move(queue_.front()); // ✅ Moves the object
        //Since we're calling queue_.pop() right after, the original object will be destroyed anyway. 
        // Using std::move() allows us to "steal" its resources instead of copying them.
        queue_.pop(); 
        cv_.notify_one(); // Notify waiting producers
        return item;
    }
    
    // Pop with timeout (returns false if timeout or queue closed and empty)
    template<typename Rep, typename Period>
    bool pop_for(T& item, const std::chrono::duration<Rep, Period>& timeout) {
        std::unique_lock<std::mutex> lock(mtx_);
        
        if (!cv_.wait_for(lock, timeout, [this] { return !queue_.empty() || closed_; })) {
            return false; // Timeout
        }
        
        if (queue_.empty() && closed_) {
            return false; // Queue is closed and empty
        }
        
        item = std::move(queue_.front());
        queue_.pop();
        cv_.notify_one();
        return true;
    }
    
    // Alternative: Pop with timeout using optional (C++17)
    template<typename Rep, typename Period>
    std::optional<T> pop_for_optional(const std::chrono::duration<Rep, Period>& timeout) {
        std::unique_lock<std::mutex> lock(mtx_);
        
        if (!cv_.wait_for(lock, timeout, [this] { return !queue_.empty() || closed_; })) {
            return std::nullopt; // Timeout
        }
        
        if (queue_.empty() && closed_) {
            return std::nullopt; // Queue is closed and empty
        }
        
        T item = std::move(queue_.front());
        queue_.pop();
        cv_.notify_one();
        return item;
    }
    
    // Try to pop without blocking (returns false if empty)
    bool try_pop(T& item) {
        std::lock_guard<std::mutex> lock(mtx_);
        
        if (queue_.empty()) {
            return false;
        }
        
        item = std::move(queue_.front());
        queue_.pop();
        cv_.notify_one();
        return true;
    }
    
    // Close the queue (no more pushes allowed, but existing items can be popped)
    void close() {
        std::lock_guard<std::mutex> lock(mtx_);
        closed_ = true;
        cv_.notify_all(); // Wake up all waiting threads
    }
    
    // Check if queue is empty
    bool empty() const {
        std::lock_guard<std::mutex> lock(mtx_);
        return queue_.empty();
    }
    
    // Get current size
    size_t size() const {
        std::lock_guard<std::mutex> lock(mtx_);
        return queue_.size();
    }
    
    // Check if queue is closed
    bool is_closed() const {
        std::lock_guard<std::mutex> lock(mtx_);
        return closed_;
    }
    
    // Get maximum size
    size_t max_size() const {
        return max_size_;
    }
};

// Example usage
void producer(SmartQueue<int>& queue, int id) {
    for (int i = 0; i < 10; ++i) {
        try {
            int item = id * 100 + i;
            queue.push(item);
            std::cout << "Producer " << id << " produced: " << item 
                      << " (queue size: " << queue.size() << ")" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        } catch (const std::exception& e) {
            std::cout << "Producer " << id << " error: " << e.what() << std::endl;
            break;
        }
    }
    std::cout << "Producer " << id << " finished" << std::endl;
}

void consumer(SmartQueue<int>& queue, int id) {
    while (true) {
        try {
            int item = queue.pop();
            std::cout << "Consumer " << id << " consumed: " << item 
                      << " (queue size: " << queue.size() << ")" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        } catch (const std::exception& e) {
            std::cout << "Consumer " << id << " finished: " << e.what() << std::endl;
            break;
        }
    }
}

int main() {
    // Create a smart queue with max size of 5
    SmartQueue<int> smart_queue(5);
    
    std::cout << "=== SmartQueue Demo ===" << std::endl;
    std::cout << "Max queue size: " << smart_queue.max_size() << std::endl;
    
    // Demo of pop_for usage patterns
    std::cout << "\n=== Demo: pop_for usage patterns ===" << std::endl;
    
    // Add some items for demo
    smart_queue.push(42);
    smart_queue.push(100);
    
    // Method 1: Using reference parameter
    int item1;
    if (smart_queue.pop_for(item1, std::chrono::milliseconds(100))) {
        std::cout << "Method 1 - Got item: " << item1 << std::endl;
    } else {
        std::cout << "Method 1 - Timeout or queue closed" << std::endl;
    }
    
    // Method 2: Using optional return
    auto result = smart_queue.pop_for_optional(std::chrono::milliseconds(100));
    if (result.has_value()) {
        std::cout << "Method 2 - Got item: " << result.value() << std::endl;
    } else {
        std::cout << "Method 2 - Timeout or queue closed" << std::endl;
    }
    
    // Test timeout
    auto timeout_result = smart_queue.pop_for_optional(std::chrono::milliseconds(100));
    if (timeout_result.has_value()) {
        std::cout << "Got item: " << timeout_result.value() << std::endl;
    } else {
        std::cout << "Timeout - queue was empty" << std::endl;
    }
    
    std::cout << "\n=== Producer-Consumer Demo ===" << std::endl;
    
    // Create producer and consumer threads
    std::thread p1(producer, std::ref(smart_queue), 1);
    std::thread p2(producer, std::ref(smart_queue), 2);
    std::thread c1(consumer, std::ref(smart_queue), 1);
    std::thread c2(consumer, std::ref(smart_queue), 2);
    
    // Wait for producers to finish
    p1.join();
    p2.join();
    
    std::cout << "\nProducers finished. Closing queue..." << std::endl;
    
    // Close the queue to signal consumers
    smart_queue.close();
    
    // Wait for consumers to finish
    c1.join();
    c2.join();
    
    std::cout << "\nAll threads finished." << std::endl;
    std::cout << "Final queue size: " << smart_queue.size() << std::endl;
    
    return 0;
}
