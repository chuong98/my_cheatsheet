"""
CLASS DECORATORS IN PYTHON

Two main approaches:
1. Decorator AS a class (using __call__)
2. Decorator ON a class (decorating whole class)
"""

print("="*60)
print("1. DECORATOR AS A CLASS (using __call__)")
print("="*60)

class CountCalls:
    """Decorator implemented as a class."""
    
    def __init__(self, func):
        self.func = func
        self.count = 0
    
    def __call__(self, *args, **kwargs):
        """Make instance callable like a function."""
        self.count += 1
        print(f"Call {self.count} of {self.func.__name__}")
        return self.func(*args, **kwargs)


@CountCalls
def say_hello(name):
    return f"Hello, {name}!"


# Now say_hello is an instance of CountCalls
print(say_hello("Alice"))
print(say_hello("Bob"))
print(say_hello("Charlie"))
print(f"Total calls: {say_hello.count}")


print("\n" + "="*60)
print("2. CLASS DECORATOR WITH PARAMETERS")
print("="*60)

class Repeat:
    """Decorator class that accepts parameters."""
    
    def __init__(self, times):
        self.times = times
    
    def __call__(self, func):
        """Called when decorator is applied to function."""
        def wrapper(*args, **kwargs):
            for i in range(self.times):
                result = func(*args, **kwargs)
            return result
        return wrapper


@Repeat(times=3)
def greet(name):
    print(f"Hello, {name}!")


greet("World")


print("\n" + "="*60)
print("3. DECORATOR ON A CLASS")
print("="*60)

def add_str_method(cls):
    """Decorator that adds a __str__ method to a class."""
    def __str__(self):
        return f"{cls.__name__}({', '.join(f'{k}={v}' for k, v in self.__dict__.items())})"
    cls.__str__ = __str__
    return cls


@add_str_method
class Person:
    def __init__(self, name, age):
        self.name = name
        self.age = age


person = Person("Alice", 30)
print(person)  # Uses the added __str__ method


print("\n" + "="*60)
print("4. SINGLETON PATTERN (Class Decorator)")
print("="*60)

def singleton(cls):
    """Ensure only one instance of class exists."""
    instances = {}
    
    def get_instance(*args, **kwargs):
        if cls not in instances:
            instances[cls] = cls(*args, **kwargs)
        return instances[cls]
    
    return get_instance


@singleton
class Database:
    def __init__(self):
        print("Database instance created")
        self.connection = "Connected"


# Try to create multiple instances
db1 = Database()
db2 = Database()
db3 = Database()

print(f"db1 is db2: {db1 is db2}")  # True - same instance
print(f"db1 is db3: {db1 is db3}")  # True - same instance


print("\n" + "="*60)
print("5. DATACLASS-LIKE DECORATOR")
print("="*60)

def auto_repr(cls):
    """Add automatic __repr__ to class."""
    def __repr__(self):
        attrs = ', '.join(f'{k}={v!r}' for k, v in self.__dict__.items())
        return f'{cls.__name__}({attrs})'
    cls.__repr__ = __repr__
    return cls


@auto_repr
class Book:
    def __init__(self, title, author, year):
        self.title = title
        self.author = author
        self.year = year


book = Book("1984", "George Orwell", 1949)
print(book)


print("\n" + "="*60)
print("6. METHOD TIMING DECORATOR (Class-based)")
print("="*60)

import time

class Timer:
    """Decorator class to time function execution."""
    
    def __init__(self, func):
        self.func = func
        self.total_time = 0
        self.calls = 0
    
    def __call__(self, *args, **kwargs):
        start = time.time()
        result = self.func(*args, **kwargs)
        elapsed = time.time() - start
        
        self.total_time += elapsed
        self.calls += 1
        
        print(f"{self.func.__name__} took {elapsed:.4f}s")
        return result
    
    def stats(self):
        avg = self.total_time / self.calls if self.calls > 0 else 0
        return f"Total: {self.total_time:.4f}s, Calls: {self.calls}, Avg: {avg:.4f}s"


@Timer
def process_data(n):
    time.sleep(0.01 * n)
    return n * 2


process_data(1)
process_data(2)
process_data(3)
print(f"Stats: {process_data.stats()}")


print("\n" + "="*60)
print("7. VALIDATE ATTRIBUTES (Class Decorator)")
print("="*60)

def validate_attributes(cls):
    """Add validation to class __init__."""
    original_init = cls.__init__
    
    def new_init(self, *args, **kwargs):
        original_init(self, *args, **kwargs)
        # Validation after initialization
        if hasattr(self, 'age') and self.age < 0:
            raise ValueError("Age cannot be negative")
        if hasattr(self, 'name') and not self.name:
            raise ValueError("Name cannot be empty")
    
    cls.__init__ = new_init
    return cls


@validate_attributes
class Student:
    def __init__(self, name, age):
        self.name = name
        self.age = age


try:
    student1 = Student("Alice", 20)
    print(f"Created: {student1.name}, {student1.age}")
    
    student2 = Student("Bob", -5)  # This will raise ValueError
except ValueError as e:
    print(f"Validation error: {e}")


print("\n" + "="*60)
print("COMPARISON: Function vs Class Decorators")
print("="*60)

print("""
Function Decorator:
    def decorator(func):
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        return wrapper

Class Decorator (as decorator):
    class Decorator:
        def __init__(self, func):
            self.func = func
        
        def __call__(self, *args, **kwargs):
            return self.func(*args, **kwargs)

Benefits of class-based decorators:
- Can maintain state (instance variables)
- More organized for complex logic
- Can have multiple methods
- Good for decorators with parameters

When to use each:
- Simple logic → Function decorator
- Need state/complex behavior → Class decorator
- Decorating a class → Either works
""")