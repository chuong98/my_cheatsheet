#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <memory>
#include <chrono>
#include <vector>

// Professional thread-safe queue template
template<typename T>
class ThreadSafeQueue {
private:
    mutable std::mutex mtx_;
    std::queue<T> queue_;
    std::condition_variable condition_;
    std::atomic<bool> shutdown_{false};

public:
    ThreadSafeQueue() = default;
    
    // Disable copy operations for thread safety
    ThreadSafeQueue(const ThreadSafeQueue&) = delete;
    ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;

    // Push with move semantics for efficiency
    void push(T item) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (shutdown_.load()) {
            throw std::runtime_error("Queue is shutdown");
        }
        queue_.push(std::move(item)); // Move for efficiency
        condition_.notify_one();
    }

    // Non-blocking pop with optional return
    std::optional<T> try_pop() {
        std::lock_guard<std::mutex> lock(mtx_);
        if (queue_.empty()) {
            return std::nullopt;
        }
        T result = std::move(queue_.front()); // Move out for efficiency
        queue_.pop();
        return result;
    }

    // Blocking pop with timeout
    template<typename Rep, typename Period>
    std::optional<T> wait_and_pop(const std::chrono::duration<Rep, Period>& timeout) {
        std::unique_lock<std::mutex> lock(mtx_);
        
        if (condition_.wait_for(lock, timeout, [this] { 
            return !queue_.empty() || shutdown_.load(); 
        })) {
            if (shutdown_.load() && queue_.empty()) {
                return std::nullopt;
            }
            T result = std::move(queue_.front()); // Move for efficiency
            queue_.pop();
            return result;
        }
        return std::nullopt; // Timeout
    }

    // Graceful shutdown
    void shutdown() {
        {
            std::lock_guard<std::mutex> lock(mtx_);
            shutdown_.store(true);
        }
        condition_.notify_all();
    }

    bool is_shutdown() const {
        return shutdown_.load();
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(mtx_);
        return queue_.size();
    }
};

// Example data structure
struct WorkItem {
    int id;
    std::string data;
    std::vector<int> payload;

    WorkItem(int i, std::string d, std::vector<int> p) 
        : id(i), data(std::move(d)), payload(std::move(p)) {} // Move in constructor

    // Move constructor for efficiency
    WorkItem(WorkItem&& other) noexcept 
        : id(other.id), data(std::move(other.data)), payload(std::move(other.payload)) {}
};

// Professional producer class
class Producer {
private:
    ThreadSafeQueue<WorkItem>& queue_;
    std::atomic<bool> should_stop_{false};

public:
    explicit Producer(ThreadSafeQueue<WorkItem>& queue) : queue_(queue) {}

    void run() {
        for (int i = 0; i < 20 && !should_stop_.load(); ++i) {
            // Create work item with move semantics
            std::vector<int> large_payload(1000, i);
            WorkItem item(i, "Task_" + std::to_string(i), std::move(large_payload));
            
            try {
                queue_.push(std::move(item)); // Move into queue
                std::cout << "Producer: Created task " << i << std::endl;
                
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            } catch (const std::exception& e) {
                std::cout << "Producer error: " << e.what() << std::endl;
                break;
            }
        }
        std::cout << "Producer finished" << std::endl;
    }

    void stop() {
        should_stop_.store(true);
    }
};

// Professional consumer class
class Consumer {
private:
    ThreadSafeQueue<WorkItem>& queue_;
    std::atomic<bool> should_stop_{false};
    int consumer_id_;

public:
    Consumer(ThreadSafeQueue<WorkItem>& queue, int id) 
        : queue_(queue), consumer_id_(id) {}

    void run() {
        while (!should_stop_.load()) {
            auto item = queue_.wait_and_pop(std::chrono::milliseconds(500));
            
            if (item.has_value()) {
                // Process the work item (moved out of queue)
                processWorkItem(std::move(item.value())); // Move to processing
            } else if (queue_.is_shutdown()) {
                break;
            }
            // Timeout - continue loop
        }
        std::cout << "Consumer " << consumer_id_ << " finished" << std::endl;
    }

    void stop() {
        should_stop_.store(true);
    }

private:
    void processWorkItem(WorkItem item) { // Receives by move
        std::cout << "Consumer " << consumer_id_ 
                  << ": Processing task " << item.id 
                  << " with " << item.payload.size() << " elements" << std::endl;
        
        // Simulate work
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
};

// Professional application class
class ProducerConsumerApp {
private:
    ThreadSafeQueue<WorkItem> queue_;
    std::vector<std::unique_ptr<Producer>> producers_;
    std::vector<std::unique_ptr<Consumer>> consumers_;
    std::vector<std::thread> threads_;

public:
    void start(int num_producers = 2, int num_consumers = 3) {
        // Create producers
        for (int i = 0; i < num_producers; ++i) {
            producers_.push_back(std::make_unique<Producer>(queue_));
        }

        // Create consumers
        for (int i = 0; i < num_consumers; ++i) {
            consumers_.push_back(std::make_unique<Consumer>(queue_, i));
        }

        // Start producer threads
        for (auto& producer : producers_) {
            threads_.emplace_back(&Producer::run, producer.get());
        }

        // Start consumer threads
        for (auto& consumer : consumers_) {
            threads_.emplace_back(&Consumer::run, consumer.get());
        }

        std::cout << "Started " << num_producers << " producers and " 
                  << num_consumers << " consumers" << std::endl;
    }

    void shutdown() {
        // Stop producers first
        for (auto& producer : producers_) {
            producer->stop();
        }

        // Wait for producers to finish
        for (size_t i = 0; i < producers_.size(); ++i) {
            if (threads_[i].joinable()) {
                threads_[i].join();
            }
        }

        // Allow consumers to finish remaining work
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // Shutdown queue and consumers
        queue_.shutdown();
        for (auto& consumer : consumers_) {
            consumer->stop();
        }

        // Wait for all consumer threads
        for (size_t i = producers_.size(); i < threads_.size(); ++i) {
            if (threads_[i].joinable()) {
                threads_[i].join();
            }
        }

        std::cout << "Application shutdown complete" << std::endl;
    }
};

int main() {
    std::cout << "=== Professional Producer-Consumer Pattern ===" << std::endl;
    
    ProducerConsumerApp app;
    app.start(2, 3); // 2 producers, 3 consumers
    
    // Let it run for a while
    std::this_thread::sleep_for(std::chrono::seconds(5));
    
    app.shutdown();
    
    return 0;
}