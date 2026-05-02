"""
The Descriptor Protocol is a powerful low-level feature in Python that allows you to define how attribute access (getting, setting, and deleting) is handled. It is the underlying mechanism that powers many of Python's most famous features, including @property, @classmethod, @staticmethod, and even regular instance methods.


At its core, a descriptor is simply an object that implements at least one of the three "magic" methods of the protocol.

1. The Three Methods of the Protocol
When an object is defined as a class attribute and implements any of these methods, it becomes a descriptor.

- __get__(self, instance, owner): This method is called to retrieve an attribute from an instance. e.g: value = obj.attr
- __set__(self, instance, value): This method is called to set an attribute on an instance. e.g: obj.attr = value
- __delete__(self, instance): This method is called to delete an attribute from an instance. e.g: del obj.attr

Why use Descriptors over Properties?
- Reusability: If you have 10 attributes that all need "uppercase validation," you write the descriptor once. With @property, you would have to write 10 separate getters and setters.
- Separation of Concerns: Complex validation logic is moved out of your main data class and into a dedicated validation object.

"""

class ValidatedString:
    def __init__(self, storage_name):
        self.storage_name = storage_name

    def __get__(self, instance, owner):
        # If accessed via the class (not instance), return the descriptor itself
        if instance is None:
            return self
        print(f"Retrieving {self.storage_name}")
        # In a descriptor, we cannot use return instance.username 
        # because that would call the descriptor's __get__ method again, 
        # leading to an infinite loop. 
        # Instead, we access the object's internal storage directly.
        
        # Why use .__dict__?
        # Every standard Python object (unless it uses __slots__) has a __dict__ attribute. This is where your data actually lives.
        # When you write u.age = 25, Python usually does this:
        # - It checks if age is a descriptor.
        # - If it is, it calls __set__.
        #   + Inside __set__, we manually put the value into the dictionary: instance.__dict__['age'] = 25.
        # - When you later read the value, the descriptor goes back into that dictionary to find exactly what it stored earlier.
        return instance.__dict__.get(self.storage_name)

    def __set__(self, instance, value):
        if not isinstance(value, str):
            raise ValueError(f"{self.storage_name} must be a string")
        print(f"Setting {self.storage_name} to {value.upper()}")
        # In a descriptor, we cannot use return instance.username 
        # because that would call the descriptor's __get__ method again, 
        # leading to an infinite loop. 
        # Instead, we access the object's internal storage directly.
        instance.__dict__[self.storage_name] = value.upper()

    def __delete__(self, instance):
        print(f"Deletion of {self.storage_name} is restricted!")
        raise AttributeError("This attribute cannot be deleted")

class User:
    # The descriptor is defined as a class attribute
    username = ValidatedString("username")

# Usage
u = User()
u.username = "alice"  # Triggers __set__ -> Stores "ALICE"
print(u.username)      # Triggers __get__ -> "ALICE"
# del u.username      # Triggers __delete__ -> Raises AttributeError