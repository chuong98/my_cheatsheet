#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int shared_data = 0;

void worker_function() {
    // assume by accident, the mutex was manually locked
    mtx.lock();
    
    // Use adopt_lock to take ownership of already locked mutex. 
    // It will not deadlock, as the mutex is already locked by this thread.
    std::lock_guard<std::mutex> lock(mtx, std::adopt_lock);
    
    // Critical section
    shared_data++;
    std::cout << "Thread " << std::this_thread::get_id() 
              << " incremented shared_data to " << shared_data << std::endl;
    
    // lock_guard will automatically unlock when it goes out of scope
}

int main() {
    std::thread t1(worker_function);
    std::thread t2(worker_function);
    std::thread t3(worker_function);
    
    t1.join();
    t2.join();
    t3.join();
    
    std::cout << "Final value of shared_data: " << shared_data << std::endl;
    
    return 0;
}