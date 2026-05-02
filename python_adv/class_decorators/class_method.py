from datetime import datetime
"""
Example demonstrating various use cases of classmethod in Python.
- can use to create alternative constructors (factory methods). 
    Instead of using the default __init__ method, we can define multiple classmethods that return instances of the class in different ways.
    ex: Person(name, birth_year) vs Person.from_birth_date(name, birth_date) vs Person.from_age(name, age)
- can be used to manage class-level state or configuration, like class variables, accessing and modifying the default value
- can be inherited and overridden in subclasses, allowing for polymorphic behavior.
""" 


class Person:
    """Example demonstrating classmethod use cases."""
    DEFAULT_ROLE = "General Staff"

    def __init__(self, name: str, birth_year: int) -> None:
        self.name = name
        self.birth_year = birth_year

    # Use case 1: Alternative constructors (Factory methods)
    @classmethod
    def from_birth_date(cls, name: str, birth_date: str):
        """Create Person from birth date string (YYYY-MM-DD)."""
        year = int(birth_date.split("-")[0])
        return cls(name, year) # calls Person(name, year) __init__ method

    @classmethod
    def from_age(cls, name: str, age: int):
        """Create Person from current age."""
        current_year = datetime.now().year
        birth_year = current_year - age
        return cls(name, birth_year) # calls Person(name, year) __init__ method

    def get_age(self) -> int:
        """Regular instance method."""
        return datetime.now().year - self.birth_year

    @classmethod
    def get_default_role(cls):
        # Accesses the class (cls) to retrieve the value
        return f"Default Role: {cls.DEFAULT_ROLE}"
    
    def __repr__(self) -> str:
        return f"Person(name='{self.name}', birth_year={self.birth_year})"


class Config:
    """Example: Using classmethod to manage class-level state."""

    _instance_count = 0
    _debug_mode = False

    def __init__(self, name: str) -> None:
        self.name = name
        Config._instance_count += 1

    @classmethod
    def set_debug_mode(cls, enabled: bool):
        """Change class-level configuration."""
        cls._debug_mode = enabled
        print(f"Debug mode: {'ON' if enabled else 'OFF'}")

    @classmethod
    def get_instance_count(cls) -> int:
        """Access class-level data."""
        return cls._instance_count

    @classmethod
    def reset_count(cls):
        """Modify class-level data."""
        cls._instance_count = 0


class Manager(Person):
    DEFAULT_ROLE = "Management"


# Example with inheritance
class Employee(Person):
    """Inheriting classmethod behavior."""
    DEFAULT_ROLE = "General Staff"

    def __init__(self, name: str, birth_year: int, employee_id: str) -> None:
        super().__init__(name, birth_year)
        self.employee_id = employee_id

    @classmethod
    def from_age(cls, name: str, age: int, employee_id: str = "N/A"):
        """Override to add employee_id parameter."""
        current_year = datetime.now().year
        birth_year = current_year - age
        return cls(name, birth_year, employee_id)


if __name__ == "__main__":
    print("=== Use Case 1: Alternative Constructors ===")
    # Normal constructor
    p1 = Person("Alice", 1990)
    print(f"{p1} -> Age: {p1.get_age()}")

    # Using classmethod factory
    p2 = Person.from_birth_date("Bob", "1985-05-15")
    print(f"{p2} -> Age: {p2.get_age()}")

    p3 = Person.from_age("Charlie", 30)
    print(f"{p3} -> Age: {p3.get_age()}")

    print("\n=== Use Case 2: Class-Level State Management ===")
    Config.set_debug_mode(True)
    c1 = Config("config1")
    c2 = Config("config2")
    print(f"Total instances created: {Config.get_instance_count()}")
    c1._debug_mode = False  # Instance-level change does not affect class-level
    print(f"c1 debug mode: {c1._debug_mode}, c2 debug mode: {c2._debug_mode}")

    print("\n=== Use Case 3: Inheritance ===")
    # Classmethod returns correct subclass instance
    emp = Employee.from_age("Diana", 28, "EMP001")
    print(f"{emp}")
    print(f"Type: {type(emp)}")  # Shows Employee, not Person!

    print("\n === Use Case 4: Accessing Class-Level Data ===")
    print(Person.get_default_role())   # Output: Default Role: General Staff
    print(Manager.get_default_role())  # Output: Default Role: Management
    print(Employee.get_default_role()) # Output: Default Role: General Staff