from abc import ABC, abstractmethod
"""
 Registering Virtual Subclasses with ABC.register()
 - Allows a class to be recognized as a subclass of an ABC without actual inheritance
 - Useful for duck typing and flexible designs
 - Note: Registered classes are not required to implement abstract methods
 
 DUCK TYPING:
 - "If it walks like a duck and quacks like a duck, then it's a duck"
 - Focus on what an object CAN DO (methods/attributes), not what it IS (type)
 - Python's philosophy: don't check types, just try to use it!
"""

print("="*60)
print("DUCK TYPING EXAMPLES")
print("="*60)

# Example 1: Different types, same interface
class Duck:
    def swim(self):
        return "Duck swimming"
    
    def quack(self):
        return "Quack!"

class Person:
    def swim(self):
        return "Person swimming"
    
    def quack(self):
        return "Person imitating: Quack!"

class Boat:
    def swim(self):
        return "Boat floating"
    
    # Note: Boat doesn't have quack()!

# Duck typing in action: we don't care about the TYPE
def make_it_swim(thing):
    """Accepts anything that has a swim() method."""
    return thing.swim()  # Don't check type, just use it!

def make_it_perform(thing):
    """Duck typing: try to use it, handle if it fails."""
    print(thing.swim())
    try:
        print(thing.quack())
    except AttributeError:
        print("(Can't quack)")

duck = Duck()
person = Person()
boat = Boat()

print("\nCalling make_it_swim():")
print(make_it_swim(duck))    # Works
print(make_it_swim(person))  # Works
print(make_it_swim(boat))    # Works - boat is not an animal, but has swim()!

print("\nCalling make_it_perform():")
make_it_perform(duck)
make_it_perform(person)
make_it_perform(boat)  # swim works, quack fails gracefully


# Example 2: File-like objects (classic duck typing)
print("\n" + "="*60)
print("FILE-LIKE OBJECTS (Classic Duck Typing)")
print("="*60)

class FakeFile:
    """Behaves like a file, but isn't one."""
    def __init__(self):
        self.content = []
    
    def write(self, text):
        self.content.append(text)
    
    def read(self):
        return "".join(self.content)

def save_data(file_object):
    """Accepts anything with a write() method - duck typing!"""
    file_object.write("Hello, ")
    file_object.write("World!")

# Works with real file
import io
real_file = io.StringIO()
save_data(real_file)
print(f"Real file content: {real_file.getvalue()}")

# Works with fake file
fake_file = FakeFile()
save_data(fake_file)
print(f"Fake file content: {fake_file.read()}")


print("\n" + "="*60)
print("ABC.register() WITH DUCK TYPING")
print("="*60)


class Animal(ABC):
    """Abstract base class for animals."""
    
    @abstractmethod
    def make_sound(self):
        pass

class Dog(Animal):
    """Real subclass - must implement abstract methods."""
    def make_sound(self):
        return "Woof!"


# Robot doesn't inherit from Animal, but we can "register" it
class Robot:
    """Completely independent class."""
    def beep(self):
        return "Beep boop!"
    
    # Note: Robot doesn't implement make_sound()!


# Register Robot as a "virtual subclass" of Animal
Animal.register(Robot)

print(f"\nDog is subclass of Animal? {issubclass(Dog, Animal)}")  # True (real inheritance)
print(f"Robot is subclass of Animal? {issubclass(Robot, Animal)}")  # True (virtual!)

dog = Dog()
robot = Robot()

print(f"\ndog isinstance of Animal? {isinstance(dog, Animal)}")  # True
print(f"robot isinstance of Animal? {isinstance(robot, Animal)}")  # True (virtual!)

# But Robot doesn't actually have Animal's interface!
print(f"\nDog can make_sound: {dog.make_sound()}")
# print(f"Robot can make_sound: {robot.make_sound()}")  # AttributeError!
print(f"Robot can beep: {robot.beep()}")

