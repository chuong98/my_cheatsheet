"""
Example:
You need to add a new feature to calculate discounts for different customer types without modifying the existing `DiscountCalculator` class. What approach should you use?
Strategy Pattern:
- Define a family of algorithms (discount strategies)
- Encapsulate each algorithm in a separate class
- Make them interchangeable within the context (DiscountCalculator)
- Allows adding new strategies without changing existing code
- Adheres to the Open/Closed Principle (open for extension, closed for modification)
"""

from abc import ABC, abstractmethod
# Strategy Interface
class DiscountStrategy(ABC):
    @abstractmethod
    def calculate_discount(self, amount: float) -> float:
        pass
# Concrete Strategies
class NoDiscount(DiscountStrategy):
    def calculate_discount(self, amount: float) -> float:
        return 0.0
class SeasonalDiscount(DiscountStrategy):
    def calculate_discount(self, amount: float) -> float:
        return amount * 0.10  # 10% discount
class VIPDiscount(DiscountStrategy):
    def calculate_discount(self, amount: float) -> float:
        return amount * 0.20  # 20% discount
# Context: Main class using the strategy
class DiscountCalculator:
    def __init__(self, strategy: DiscountStrategy) -> None:
        self._strategy = strategy

    def set_strategy(self, strategy: DiscountStrategy) -> None:
        self._strategy = strategy

    def calculate_final_price(self, amount: float) -> float:
        discount = self._strategy.calculate_discount(amount)
        return amount - discount
# Usage
if __name__ == "__main__":
    amount = 100.0

    # No Discount
    calculator = DiscountCalculator(NoDiscount())
    print(f"No Discount: Final Price = {calculator.calculate_final_price(amount):.2f}")

    # Seasonal Discount
    calculator.set_strategy(SeasonalDiscount())
    print(f"Seasonal Discount: Final Price = {calculator.calculate_final_price(amount):.2f}")

    # VIP Discount
    calculator.set_strategy(VIPDiscount())
    print(f"VIP Discount: Final Price = {calculator.calculate_final_price(amount):.2f}")