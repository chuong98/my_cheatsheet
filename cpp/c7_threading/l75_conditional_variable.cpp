#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

class ProducerConsumer {
private:
    std::queue<int> buffer;
    std::mutex mtx;
    std::condition_variable cv;
    bool finished = false;
    const size_t max_size = 5;

public:
    void producer(int id) {
        for (int i = 0; i < 10; ++i) {
            std::unique_lock<std::mutex> lock(mtx); //unique_lock is required for condition_variable

            // Wait until buffer has space, then lock the mutex, to add an item to the buffer
            cv.wait(lock, [this] { return buffer.size() < max_size; });
            
            int item = id * 100 + i;
            buffer.push(item);
            std::cout << "Producer " << id << " produced: " << item << std::endl;
            
            cv.notify_all(); // Notify all waiting consumers
            
            lock.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    
    void consumer(int id) {
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            
            // Wait until buffer has items or production is finished
            cv.wait(lock, [this] { return !buffer.empty() || finished; });
            
            if (buffer.empty() && finished) {
                break;
            }
            
            if (!buffer.empty()) {
                int item = buffer.front();
                buffer.pop();
                std::cout << "Consumer " << id << " consumed: " << item << std::endl;
                
                cv.notify_one(); // Notify one waiting producer
            }
            
            lock.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }
    }
    
    void finish() {
        std::lock_guard<std::mutex> lock(mtx);
        finished = true;
        cv.notify_all(); // Wake up all waiting consumers
    }
};

int main() {
    ProducerConsumer pc;
    
    // Create producer and consumer threads
    std::thread p1(&ProducerConsumer::producer, &pc, 1);
    std::thread p2(&ProducerConsumer::producer, &pc, 2);
    std::thread c1(&ProducerConsumer::consumer, &pc, 1);
    std::thread c2(&ProducerConsumer::consumer, &pc, 2);
    
    // Wait for producers to finish
    p1.join();
    p2.join();
    
    // Signal that production is finished
    pc.finish();
    
    // Wait for consumers to finish
    c1.join();
    c2.join();
    
    std::cout << "All threads finished." << std::endl;
    
    return 0;
}