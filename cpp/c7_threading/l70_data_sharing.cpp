#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

/* To share data between threads,
- passed-in data can be global.
- the threading functions are the members of the class, that they can share the class members.
- using mutex to protect shared data from race conditions
*/

class SharedData {
private:
    int counter;
    std::mutex mtx;

public:
    SharedData() : counter(0) {}

    void increment() {
        //use lock_guard to automatically unlock the mutex when out of scope
        // other threads will be blocked until the mutex is unlocked
        // other options are unique_lock and scoped_lock.
        // - unique_lock allows manual unlocking and re-locking, beside auto unlocking like lock_guard
        // - scoped_lock is similar to lock_guard but can be used with condition variables
        std::lock_guard<std::mutex> lock(mtx);
        ++counter;
        std::cout << "Thread " << std::this_thread::get_id() << " incremented counter to: " << counter << std::endl;
    }

    void decrement() {
        std::lock_guard<std::mutex> lock(mtx);
        --counter;
        std::cout << "Thread " << std::this_thread::get_id() << " decremented counter to: " << counter << std::endl;
    }

    int getValue() {
        std::lock_guard<std::mutex> lock(mtx);
        return counter;
    }
};

void worker1(SharedData& data) {
    for (int i = 0; i < 5; ++i) {
        data.increment();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void worker2(SharedData& data) {
    for (int i = 0; i < 3; ++i) {
        data.decrement();
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

int main() {
    SharedData sharedData;
    // when the function requires passing a reference, using std::ref to convert it to a reference wrapper
    std::thread t1(worker1, std::ref(sharedData)); //use std::thread to initialize a threading object
    std::thread t2(worker2, std::ref(sharedData));

    t1.join(); // Wait for thread 1 to finish
    t2.join(); // Wait for thread 2 to finish

    std::cout << "Final counter value: " << sharedData.getValue() << std::endl;

    return 0;
}

/* While unique_lock is indeed more flexible than lock_guard, there are several important reasons why lock_guard is often preferred as the default choice:

1. Performance Overhead
lock_guard is lighter and faster because:
- Smaller object size (less memory)
- No additional state tracking
- Simpler implementation = better compiler optimization
- Zero runtime overhead for the extra features you don't use

unique_lock has overhead because:
- Stores additional state (whether it owns the lock)
- Supports deferred locking, timed locking, etc.
- More complex internal logic

2. RAII and Safety
lock_guard follows the principle of "make simple things simple":
- Automatic lock on construction, unlock on destruction
- No way to accidentally forget to unlock
- No risk of manual lock/unlock errors
- Clear intent: "lock this scope and that's it"
unique_lock with manual operations can introduce bugs:
- Forgetting to unlock
- Double unlocking
- Unlocking in the wrong order

*/