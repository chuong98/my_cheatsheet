"""
The Factory pattern provides an interface for creating objects but allows subclasses to alter the type of objects that will be created. 
It abstracts the instantiation logic from the user.
"""

class Dog:
    def speak(self): return "Woof!"

class Cat:
    def speak(self): return "Meow!"

class PetFactory:
    @staticmethod
    def get_pet(pet_type):
        pets = {"dog": Dog(), "cat": Cat()}
        return pets.get(pet_type, Dog())

# Usage
my_pet = PetFactory.get_pet("cat")
print(my_pet.speak())  # Output: Meow!


print("\n" + "="*60)
print("STANDARD FACTORY PATTERN WITH ABSTRACT BASE")
print("="*60)

from abc import ABC, abstractmethod

# Step 1: Define abstract product interface
class Vehicle(ABC):
    """Abstract product - defines interface all vehicles must implement."""
    
    @abstractmethod
    def get_type(self) -> str:
        pass
    
    @abstractmethod
    def get_wheels(self) -> int:
        pass
    
    def describe(self) -> str:
        return f"{self.get_type()} with {self.get_wheels()} wheels"


# Step 2: Concrete products implementing the interface
class Car(Vehicle):
    def get_type(self) -> str:
        return "Car"
    
    def get_wheels(self) -> int:
        return 4


class Motorcycle(Vehicle):
    def get_type(self) -> str:
        return "Motorcycle"
    
    def get_wheels(self) -> int:
        return 2


class Truck(Vehicle):
    def get_type(self) -> str:
        return "Truck"
    
    def get_wheels(self) -> int:
        return 6


class Bicycle(Vehicle):
    def get_type(self) -> str:
        return "Bicycle"
    
    def get_wheels(self) -> int:
        return 2


# Step 3: Factory class that creates products
class VehicleFactory:
    """Factory for creating different types of vehicles."""
    
    _vehicle_types = {
        "car": Car,
        "motorcycle": Motorcycle,
        "truck": Truck,
        "bicycle": Bicycle
    }
    
    @classmethod
    def create_vehicle(cls, vehicle_type: str) -> Vehicle:
        """
        Factory method to create vehicles.
        
        Args:
            vehicle_type: Type of vehicle to create
            
        Returns:
            Vehicle instance
            
        Raises:
            ValueError: If vehicle type is unknown
        """
        vehicle_class = cls._vehicle_types.get(vehicle_type.lower())
        if vehicle_class is None:
            available = ", ".join(cls._vehicle_types.keys())
            raise ValueError(f"Unknown vehicle type: {vehicle_type}. Available: {available}")
        return vehicle_class()
    
    @classmethod
    def register_vehicle(cls, vehicle_type: str, vehicle_class: type):
        """Register a new vehicle type (extensibility)."""
        cls._vehicle_types[vehicle_type.lower()] = vehicle_class
    
    @classmethod
    def available_types(cls):
        """Get list of available vehicle types."""
        return list(cls._vehicle_types.keys())


# Usage
print("\nAvailable vehicle types:", VehicleFactory.available_types())

car = VehicleFactory.create_vehicle("car")
motorcycle = VehicleFactory.create_vehicle("motorcycle")
truck = VehicleFactory.create_vehicle("truck")

print(f"\n{car.describe()}")
print(f"{motorcycle.describe()}")
print(f"{truck.describe()}")

# Demonstrate extensibility - add new vehicle type
class ElectricScooter(Vehicle):
    def get_type(self) -> str:
        return "Electric Scooter"
    
    def get_wheels(self) -> int:
        return 2

VehicleFactory.register_vehicle("scooter", ElectricScooter)
scooter = VehicleFactory.create_vehicle("scooter")
print(f"{scooter.describe()}")

# Error handling
try:
    unknown = VehicleFactory.create_vehicle("spaceship")
except ValueError as e:
    print(f"\nError: {e}")


print("\n" + "="*60)
print("FACTORY METHOD PATTERN (Another Standard Approach)")
print("="*60)

class Document(ABC):
    """Abstract document."""
    
    @abstractmethod
    def export(self) -> str:
        pass


class PDFDocument(Document):
    def export(self) -> str:
        return "Exporting as PDF..."


class WordDocument(Document):
    def export(self) -> str:
        return "Exporting as Word document..."


class ExcelDocument(Document):
    def export(self) -> str:
        return "Exporting as Excel spreadsheet..."


# Abstract Creator
class DocumentCreator(ABC):
    """Abstract creator with factory method."""
    
    @abstractmethod
    def create_document(self) -> Document:
        """Factory method - subclasses implement this."""
        pass
    
    def export_document(self) -> str:
        """Business logic using the factory method."""
        document = self.create_document()
        return document.export()


# Concrete Creators
class PDFCreator(DocumentCreator):
    def create_document(self) -> Document:
        return PDFDocument()


class WordCreator(DocumentCreator):
    def create_document(self) -> Document:
        return WordDocument()


class ExcelCreator(DocumentCreator):
    def create_document(self) -> Document:
        return ExcelDocument()


# Usage
print("\nUsing Factory Method Pattern:")
creators = [PDFCreator(), WordCreator(), ExcelCreator()]

for creator in creators:
    print(f"{creator.__class__.__name__}: {creator.export_document()}")


print("\n" + "="*60)
print("COMPARISON: Simple Factory vs Factory Method")
print("="*60)

print("""
SIMPLE FACTORY (VehicleFactory):
- One factory class with static/class method
- Centralized object creation logic
- Easy to understand and use
- Good for: Simple cases with many product types
- Example: VehicleFactory.create_vehicle("car")

FACTORY METHOD (DocumentCreator):
- Each creator subclass implements factory method
- Follows Open/Closed Principle better
- More flexible for subclass customization
- Good for: When creation logic varies per type
- Example: PDFCreator().create_document()

When to use:
- Simple Factory → Most common cases, straightforward creation
- Factory Method → When subclasses need to customize creation process
""")

