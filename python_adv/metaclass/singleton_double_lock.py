"""
You need to implement a singleton class that is thread-safe, ensuring that only one instance is created even in a multithreaded environment.

To implement a thread-safe Singleton in Python, you must use a Lock from the threading module. 
Without a lock, two threads could check if not instance at the exact same time, both see None, and both proceed to create two separate instances, defeating the purpose of the pattern.

Why Double-Checked Locking?
- If we put the lock at the very beginning of the __call__ method, every single time you tried to access your Singleton, 
the program would pause to acquire and release a lock. This creates a significant performance bottleneck.

- By checking if cls not in cls._instances before the lock, we ensure that once the Singleton is created, 
access is nearly as fast as a standard dictionary lookup.

Breakdown of the Logic
- cls: This represents the class currently being called (e.g., DatabaseConnection).
- cls._instances: This is a dictionary where the keys are the class types and the values are the single instances of those classes.

"""

import threading

class SingletonMeta(type):
    """
    A thread-safe implementation of Singleton.
    """
    _instances = {}
    _lock: threading.Lock = threading.Lock()

    def __call__(cls, *args, **kwargs):
        # First check (optimization): if the instance already exists, 
        # return it immediately without acquiring the lock.
        if cls not in cls._instances:
            # Acquire the lock to ensure only one thread creates the instance.
            with cls._lock:
                # Second check: once we have the lock, check again in case 
                # another thread created it while we were waiting.
                if cls not in cls._instances:
                    instance = super().__call__(*args, **kwargs)
                    cls._instances[cls] = instance
        return cls._instances[cls]

# Usage
class DatabaseConnection(metaclass=SingletonMeta):
    def __init__(self):
        self.connection_string = "Loaded"
        print("Initializing heavy database connection...")

# Simulating multithreaded access
def create_connection():
    db = DatabaseConnection()
    print(f"Database connection string: {db.connection_string}")
threads = []
for i in range(5):
    thread = threading.Thread(target=create_connection)
    threads.append(thread)
    thread.start()
for thread in threads:
    thread.join()
# All threads should print the same connection string and only one initialization message should appear.    
