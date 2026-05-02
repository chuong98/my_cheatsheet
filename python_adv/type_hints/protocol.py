"""Question:
You are developing a function that works with any object having a `write` method, regardless of its class inheritance. 
You want to enforce this behavior using type hints.
Answer:
To enforce behavior based on the presence of a specific method (like write) rather than a specific class hierarchy,
the most appropriate approach is Structural Typing using typing.Protocol. Also known as "static duck typing" in type hints,
- By inheriting from Protocol, you define a template that specifies the required methods and signatures. 
- Any class that implements these methods is automatically considered a subtype of that Protocol by type checkers (like Mypy or Pyright).
"""

from typing import Protocol

# Define the Protocol
class Writable(Protocol):
    def write(self, data: str) -> int:
        """Write string data to the stream and return the number of characters written.
        
        Args:
            data (str): The string data to be written to the stream.
            
        Returns:
            int: The number of characters successfully written.
            
        Note:
            This method uses ellipsis (...) as a placeholder implementation,
            which is valid Python syntax commonly used in abstract methods,
            type stubs, and protocol definitions to indicate that the actual
            implementation should be provided by concrete classes.
        """
        ...

# The function that uses the protocol
def save_to_resource(resource: Writable, content: str):
    """ Any object with a write() method is considered Writable subclass, even it is not explicitly declared as such. 
    Thus, this enforces duck typing at the type hinting level.
    """
    resource.write(content)

# These classes don't share a base class, but both work
class FileLogger:
    def write(self, data: str) -> int:
        print(f"Writing to file: {data}")
        return len(data)

class NetworkStream:
    def write(self, data: str) -> int:
        print(f"Streaming: {data}")
        return len(data)

class DummyWrong:
    def send(self, data: str) -> int:
        print(f"Sending: {data}")
        return len(data)
# Usage
save_to_resource(FileLogger(), "Hello World")
save_to_resource(NetworkStream(), "Stream Data")
# The following line would raise a type checker error, as DummyWrong does not implement write()
save_to_resource(DummyWrong(), "This will fail type checking")