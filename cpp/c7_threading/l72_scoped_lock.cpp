#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

class BankAccount {
private:
    std::mutex mtx;
    int balance;

public:
    BankAccount(int initial_balance) : balance(initial_balance) {}

    void transfer(BankAccount& to, int amount) {
        // Use scoped_lock to lock both mutexes safely
        std::scoped_lock lock(mtx, to.mtx);
        
        if (balance >= amount) {
            balance -= amount;
            to.balance += amount;
            std::cout << "Transferred " << amount << " (Thread: " 
                      << std::this_thread::get_id() << ")\n";
        } else {
            std::cout << "Insufficient funds (Thread: " 
                      << std::this_thread::get_id() << ")\n";
        }
    }

    int get_balance() {
        std::scoped_lock lock(mtx);
        return balance;
    }
};

int main() {
    BankAccount account1(1000);
    BankAccount account2(500);

    std::vector<std::thread> threads;

    // Create multiple threads performing transfers
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([&account1, &account2, i]() {
            account1.transfer(account2, 100 + i * 10);
        });

        threads.emplace_back([&account2, &account1, i]() {
            account2.transfer(account1, 50 + i * 5);
        });
    }

    // Wait for all threads to complete
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Final balances:\n";
    std::cout << "Account 1: " << account1.get_balance() << "\n";
    std::cout << "Account 2: " << account2.get_balance() << "\n";

    return 0;
}