"""
Decorator Pattern
- allows behavior to be added to individual objects, dynamically, without affecting the behavior of other objects from the same class.
- useful for adhering to the Open/Closed Principle (open for extension, closed for modification)
- can be implemented using function decorators or class decorators in Python
Function Decorators
- a function that takes another function and extends its behavior without explicitly modifying it.
Class Decorators
- a class that takes a function and extends its behavior by implementing the __call__ method.
- can maintain state and have multiple methods, making them more suitable for complex decorators.
"""


def simple_decorator(func):
    """A simple function decorator that logs before and after a function call."""
    def wrapper(*args, **kwargs):
        print(f"Calling function '{func.__name__}' with args={args}, kwargs={kwargs}")
        result = func(*args, **kwargs)
        print(f"Function '{func.__name__}' returned {result}")
        return result
    return wrapper

@simple_decorator
def multiply(x, y):
    return x * y
result = multiply(3, 4)
print(f"Result of multiply: {result}")
