"""
You are building a Python application that needs to handle file operations. 
Specifically, you want to implement a custom context manager that ensures a file is opened and properly closed, even if an exception is raised while processing the file. 
You are required to use the `with` statement for this functionality. 
To implement a custom context manager in Python, you have two primary "correct" ways. 
- The classic approach is using a Class with special methods, and 
- the modern, more concise approach is using the contextlib generator.
"""

# Classic Approach: Using a Class with __enter__ and __exit__ methods
class FileHandler:
    def __init__(self, filename, mode):
        self.filename = filename
        self.mode = mode
        self.file = None

    def __enter__(self):
        self.file = open(self.filename, self.mode)
        return self.file

    def __exit__(self, exc_type, exc_value, traceback):
        if self.file:
            self.file.close()
        # Optionally handle exceptions here
        if exc_type is not None:
            print(f"An exception occurred: {exc_value}")
        return False  # Propagate exception if any
# Usage of the classic approach
with FileHandler('example.txt', 'w') as f:
    f.write('Hello, World!\n')
    # Uncomment the next line to simulate an exception
    # Even if an error happens here, the file closes.
    # raise ValueError("Simulated error")

# Modern Approach: Using contextlib.contextmanager
from contextlib import contextmanager
@contextmanager
def file_handler(filename, mode):
    file = open(filename, mode)
    try:
        yield file
    except Exception as e:
        print(f"An exception occurred: {e}")
        raise  # Re-raise the exception after handling
    finally:
        file.close()
# Usage of the modern approach
with file_handler('example2.txt', 'w') as f:
    f.write('Hello, World again!\n')
    # Uncomment the next line to simulate an exception
    # Even if an error happens here, the file closes.
    # raise ValueError("Simulated error in contextmanager")