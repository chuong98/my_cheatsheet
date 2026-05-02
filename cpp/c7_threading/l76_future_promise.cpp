/**
 * @file l76_future_promise.cpp
 * @brief Demonstrates std::future and std::promise for thread communication and std::async for asynchronous tasks
 * 
 * WHEN TO USE FUTURE-PROMISE:
 * 
 * Use std::future and std::promise when:
 * - You need one-time communication from a worker thread back to the main thread
 * - You want to retrieve a computed result from another thread
 * - You need thread-safe value passing without shared variables
 * - You want to synchronize threads based on completion of work
 * - You need exception safety (exceptions can be passed through promise/future)
 * 
 * Use std::async when:
 * - You want simpler syntax for launching asynchronous tasks
 * - You need automatic thread management
 * - You want the flexibility of deferred vs async execution
 * - You're doing function-style programming with return values
 * 
 * WHEN NOT TO USE FUTURE-PROMISE:
 * 
 * Avoid std::future and std::promise when:
 * - You need continuous/repeated communication between threads (use message queues instead)
 * - You need multiple consumers for the same result (future can only be consumed once)
 * - You need bidirectional communication (use condition variables + mutex instead)
 * - You're working with real-time systems where blocking is unacceptable
 * - You need to pass multiple values over time (use channels/queues instead)
 * - Performance is critical and you can't afford the overhead of heap allocation
 * - You need to cancel or interrupt the operation (future/promise don't support cancellation)
 * 
 * Advantages over other synchronization methods:
 * - No need for manual mutex/condition variable management
 * - Type-safe communication channel
 * - Built-in exception propagation
 * - Clean separation between task launching and result retrieval
 * 
 * Disadvantages:
 * - Single-use only (cannot reuse the same future/promise pair)
 * - No built-in timeout mechanism for get() operation
 * - Limited to one-way communication
 * - May involve heap allocation overhead
 * - No cancellation support
 */

/** 
 */
#include <iostream>
#include <thread>
#include <future>
#include <chrono>



// Function that performs some computation and sets the result via promise
void compute_value(std::promise<int> promise_obj, int input) {
    // Simulate some time-consuming work
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    // Perform computation
    int result = input * input;
    
    // Set the value in the promise
    promise_obj.set_value(result);
}

// Function that can be used with std::async
int compute_async(int input) {
    // Simulate some time-consuming work
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    // Perform computation and return result
    return input * input;
}

void demonstrate_async() {
    std::cout << "\n--- std::async Example ---\n";
    
    // Launch async task
    std::future<int> async_result = std::async(std::launch::async, compute_async, 15);
    
    std::cout << "Main thread: Started async computation...\n";
    
    // Do other work while computation runs
    std::cout << "Main thread: Doing other work while waiting...\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    // Get the result (blocks until ready)
    std::cout << "Main thread: Getting async result...\n";
    int result = async_result.get();
    
    std::cout << "Main thread: Async result: " << result << std::endl;
}

int main() {
    // Create a promise-future pair
    std::promise<int> promise_obj;
    std::future<int> future_obj = promise_obj.get_future();
    
    // Start a thread that will compute a value
    std::thread worker_thread(compute_value, std::move(promise_obj), 10);
    
    std::cout << "Main thread: Starting computation in background...\n";
    
    // Do other work in main thread
    std::cout << "Main thread: Doing other work while waiting...\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    // Get the result from the future (this will block until ready)
    std::cout << "Main thread: Waiting for result...\n";
    int result = future_obj.get();
    
    std::cout << "Main thread: Received result: " << result << std::endl;
    
    // Wait for the worker thread to finish
    worker_thread.join();
    
    return 0;
}