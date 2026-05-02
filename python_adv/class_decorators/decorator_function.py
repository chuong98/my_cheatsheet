"""
DECORATORS IN PYTHON

A decorator is a function that takes another function and extends its behavior
without explicitly modifying it.
- basic usage: do something before and/or after calling the original function: timming, logging, etc.
- can wrap functions with arguments and return values. Can also modify input arguments or return value
- call the original function multiple times, or not at all
Basic pattern:
    @decorator
    def function():
        pass
    
Is equivalent to:
    function = decorator(function)
"""

print("="*60)
print("1. BASIC DECORATOR")
print("="*60)

def simple_decorator(func):
    """Most basic decorator - wraps a function."""
    def wrapper():
        print("Before function call")
        func()  # Call the original function
        print("After function call")
    return wrapper


@simple_decorator
def say_hello():
    print("Hello!")


say_hello()
# Output:
# Before function call
# Hello!
# After function call


print("\n" + "="*60)
print("2. DECORATOR WITH ARGUMENTS")
print("="*60)

def decorator_with_args(func):
    """Decorator that handles function arguments."""
    def wrapper(*args, **kwargs):
        print(f"Function called with args={args}, kwargs={kwargs}")
        result = func(*args, **kwargs)  # Pass arguments to original function
        print(f"Function returned: {result}")
        return result  # Return the result
    return wrapper


@decorator_with_args
def add(a, b):
    return a + b


@decorator_with_args
def greet(name, greeting="Hello"):
    return f"{greeting}, {name}!"


result1 = add(5, 3)
print(f"Result: {result1}")

print()

result2 = greet("Alice", greeting="Hi")
print(f"Result: {result2}")


print("\n" + "="*60)
print("3. PRACTICAL EXAMPLE: TIMING DECORATOR")
print("="*60)

import time

def timing_decorator(func):
    """Measure how long a function takes to execute."""
    def wrapper(*args, **kwargs):
        start_time = time.time()
        result = func(*args, **kwargs)
        end_time = time.time()
        print(f"{func.__name__} took {end_time - start_time:.4f} seconds")
        return result
    return wrapper


@timing_decorator
def slow_function():
    time.sleep(0.1)
    return "Done!"

@timing_decorator
def fast_function():
    return sum(range(1000))


slow_function()
fast_function()


print("\n" + "="*60)
print("4. DECORATOR WITH PARAMETERS")
print("="*60)

def repeat(times):
    """Decorator that takes arguments - needs extra layer."""
    def decorator(func):
        def wrapper(*args, **kwargs):
            for i in range(times):
                print(f"Call {i + 1}:")
                result = func(*args, **kwargs)
            return result  # Return last result
        return wrapper
    return decorator


@repeat(times=3)
def say_hi(name):
    print(f"Hi, {name}!")


say_hi("Bob")


print("\n" + "="*60)
print("6. MULTIPLE DECORATORS")
print("="*60)

def bold(func):
    """Wrap output in bold markers."""
    def wrapper(*args, **kwargs):
        return "**" + func(*args, **kwargs) + "**"
    return wrapper


def italic(func):
    """Wrap output in italic markers."""
    def wrapper(*args, **kwargs):
        return "_" + func(*args, **kwargs) + "_"
    return wrapper


@bold
@italic
def get_text():
    return "Hello World"


# Decorators are applied bottom-up: italic first, then bold
print(get_text())  # **_Hello World_**


print("\n" + "="*60)
print("DECORATOR TEMPLATE")
print("="*60)

print("""
# Basic decorator template:
def my_decorator(func):
    def wrapper(*args, **kwargs):
        # Do something before
        result = func(*args, **kwargs)
        # Do something after
        return result
    return wrapper

# Decorator with parameters template:
def my_decorator(param):
    def decorator(func):
        def wrapper(*args, **kwargs):
            # Use param here
            result = func(*args, **kwargs)
            return result
        return wrapper
    return decorator
""")


print("\n" + "="*60)
print("COMMON USE CASES")
print("="*60)

print("""
Decorators are commonly used for:
- Timing/profiling functions
- Logging function calls
- Authentication/authorization checks
- Caching/memoization
- Input validation
- Rate limiting
- Retry logic
- Deprecation warnings
""")