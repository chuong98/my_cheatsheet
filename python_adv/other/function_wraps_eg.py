"""
To ensure that a decorator respects encapsulation and compatibility with OOP principles, 
the best approach is to use functools.wraps to preserve the metadata of the decorated method.

When you wrap a method in a decorator, you are essentially replacing the original function with a new "wrapper" function. 
Without proper handling, this can "leak" implementation details or hide the identity of the original method, 
breaking the expectations of other OOP structures (like introspection, debugging tools, or even inheritance behaviors).

By using functools.wraps, you ensure that the wrapper function retains the original function's name, docstring, and other attributes. 
This helps maintain the integrity of the class's interface and makes it easier to work with decorated methods in an OOP context.
"""
import functools

def log_action(func):
    @functools.wraps(func)
    def wrapper(self, *args, **kwargs):
        print(f"Executing {func.__name__} for {self}")
        return func(self, *args, **kwargs)
    return wrapper

class Account:
    @log_action
    def withdraw(self, amount):
        """Deduct money from the account."""
        pass

# Encapsulation preserved
print(Account.withdraw.__name__)  # Output: withdraw (instead of 'wrapper')
print(Account.withdraw.__doc__)   # Output: Deduct money from the account.