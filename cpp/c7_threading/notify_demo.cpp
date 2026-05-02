#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <vector>

class NotifyDemo {
private:
    std::mutex mtx_;
    std::condition_variable cv_;
    bool ready_ = false;
    int counter_ = 0;

public:
    void wait_for_signal(int thread_id) {
        std::unique_lock<std::mutex> lock(mtx_);
        
        std::cout << "Thread " << thread_id << " is waiting..." << std::endl;
        
        // Wait for signal
        cv_.wait(lock, [this] { return ready_; });
        
        std::cout << "Thread " << thread_id << " got notified! Counter: " << ++counter_ << std::endl;
        
        // Reset for next round
        if (counter_ >= 3) {
            ready_ = false;
            counter_ = 0;
        }
    }
    
    void signal_one() {
        {
            std::lock_guard<std::mutex> lock(mtx_);
            ready_ = true;
        }
        std::cout << "Signaling ONE thread..." << std::endl;
        cv_.notify_one(); // Only one thread will be woken up
    }
    
    void signal_all() {
        {
            std::lock_guard<std::mutex> lock(mtx_);
            ready_ = true;
        }
        std::cout << "Signaling ALL threads..." << std::endl;
        cv_.notify_all(); // All threads will be woken up
    }
    
    void reset() {
        std::lock_guard<std::mutex> lock(mtx_);
        ready_ = false;
        counter_ = 0;
    }
};

int main() {
    NotifyDemo demo;
    
    std::cout << "=== Demonstrating notify_one() unpredictability ===" << std::endl;
    
    // Create 3 waiting threads
    std::vector<std::thread> threads;
    for (int i = 1; i <= 3; ++i) {
        threads.emplace_back(&NotifyDemo::wait_for_signal, &demo, i);
    }
    
    // Give threads time to start waiting
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    std::cout << "\n--- Round 1: Using notify_one() ---" << std::endl;
    demo.signal_one();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    
    demo.reset();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    std::cout << "\n--- Round 2: Using notify_one() again ---" << std::endl;
    demo.signal_one();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    
    demo.reset();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    std::cout << "\n--- Round 3: Using notify_all() ---" << std::endl;
    demo.signal_all();
    
    // Wait for all threads to complete
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "\n=== Summary ===" << std::endl;
    std::cout << "Notice how notify_one() wakes up different threads unpredictably!" << std::endl;
    std::cout << "But notify_all() wakes up all remaining threads." << std::endl;
    
    return 0;
}
