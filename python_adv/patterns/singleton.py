"""
Common class inheritance patterns in Python.

1. Singleton:
    - Ensures a class has only one instance and provides a global access point to it
    - Useful for managing shared resources (e.g., database connections, logging)
    - Implemented by overriding __new__ to control instance creation
"""
class Singleton:
    _instance = None

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
        return cls._instance

# Usage
s1 = Singleton()
s2 = Singleton()
print(s1 is s2)  # Output: True

"""
While overriding __new__ is the most common way to implement a Singleton in Python, it isn't always enough on its own. 
There is a specific "trap" regarding the __init__ method that you need to be aware of.

1. The __init__ Trap
In Python, even if __new__ returns the same instance every time, __init__ is called on that instance every time you call the class.

If your __init__ sets values, they will be reset every time you "create" a new reference to the Singleton, which usually isn't what you want.
"""

class SingletonWithInit:
    _instance = None

    def __new__(cls, *args, **kwargs):  # Accept arguments
        if cls._instance is None:
            cls._instance = super().__new__(cls)
        return cls._instance

    def __init__(self, value=None):
        if not hasattr(self, 'initialized'):  # Prevent re-initialization
            self.value = value
            self.initialized = True
            print(f"Initialized with value: {value}")
        else:
            print("Instance already initialized; skipping __init__.")    

# Usage
s1 = SingletonWithInit(10)  # Initializes with value 10
s2 = SingletonWithInit(20)  # Skips re-initialization
print(s1.value)  # Output: 10
print(s1 is s2)  # Output: True