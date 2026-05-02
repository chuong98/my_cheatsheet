from abc import ABC, abstractmethod


# Abstract Base Class - defines the blueprint/interface
class Shape(ABC):
    """Abstract base class for shapes."""

    @property
    @abstractmethod
    def area(self) -> float:
        """Calculate the area of the shape."""
        pass
    
    @property
    @abstractmethod
    def perimeter(self) -> float:
        """Calculate the perimeter of the shape."""
        pass

    def describe(self) -> str:
        """Non-abstract method - shared by all subclasses."""
        return f"I am a {self.__class__.__name__} with area {self.area:.2f}"


# Concrete implementation
class Rectangle(Shape):
    """A rectangle shape."""

    def __init__(self, width: float, height: float) -> None:
        self.width = width
        self.height = height

    @property
    def area(self) -> float:
        return self.width * self.height

    @property
    def perimeter(self) -> float:
        return 2 * (self.width + self.height)


class Circle(Shape):
    """A circle shape."""

    def __init__(self, radius: float) -> None:
        self._radius = radius  # Use private attribute

    @property
    def radius(self) -> float:
        """Getter for radius."""
        return self._radius

    @radius.setter
    def radius(self, value: float) -> None:
        """Setter for radius with validation."""
        if value <= 0:
            raise ValueError("Radius must be positive")
        self._radius = value

    @property
    def area(self) -> float:
        from math import pi
        return pi * self._radius ** 2

    @property
    def perimeter(self) -> float:
        from math import pi
        return 2 * pi * self._radius


# Usage example
if __name__ == "__main__":
    # Cannot instantiate abstract class directly
    # shape = Shape()  # This would raise TypeError

    # Create concrete instances
    rect = Rectangle(5, 3)
    circle = Circle(4)

    print(rect.describe())
    print(f"Rectangle perimeter: {rect.perimeter}")

    print()

    print(circle.describe())
    print(f"Circle perimeter: {circle.perimeter:.2f}")

    # Property setter example
    print(f"\nCircle radius before: {circle.radius}")
    circle.radius = 10  # Uses the setter
    print(f"Circle radius after: {circle.radius}")
    print(f"Circle area after: {circle.area:.2f}")

    # This would raise ValueError:
    # circle.radius = -5
    # print(f"Circle perimeter: {circle.perimeter():.2f}") this would raise TypeError since perimeter is a property(float) not a method

