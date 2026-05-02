"""
Static methods don't receive self or cls as first parameter.
They behave like regular functions but belong to the class namespace.
Use when the method doesn't need access to instance or class data.
When to use static methods:

✅ Utility functions logically grouped with a class
✅ Don't need self or cls
✅ Pure functions that belong to the class's namespace
✅ Validation, formatting, or conversion helpers
"""


class StringUtils:
    """Utility class with static helper methods."""

    @staticmethod
    def is_palindrome(text: str) -> bool:
        """Check if text is a palindrome."""
        cleaned = text.lower().replace(" ", "")
        return cleaned == cleaned[::-1]

    @staticmethod
    def capitalize_words(text: str) -> str:
        """Capitalize first letter of each word."""
        return " ".join(word.capitalize() for word in text.split())

    @staticmethod
    def count_vowels(text: str) -> int:
        """Count vowels in text."""
        return sum(1 for char in text.lower() if char in "aeiou")


class MathUtils:
    """Mathematical operations as static methods."""

    @staticmethod
    def is_prime(n: int) -> bool:
        """Check if number is prime."""
        if n < 2:
            return False
        for i in range(2, int(n**0.5) + 1):
            if n % i == 0:
                return False
        return True

    @staticmethod
    def factorial(n: int) -> int:
        """Calculate factorial."""
        if n <= 1:
            return 1
        return n * MathUtils.factorial(n - 1)

    @staticmethod
    def celsius_to_fahrenheit(celsius: float) -> float:
        """Convert Celsius to Fahrenheit."""
        return (celsius * 9 / 5) + 32


class Validator:
    """Validation utilities using static methods."""

    @staticmethod
    def is_valid_email(email: str) -> bool:
        """Basic email validation."""
        return "@" in email and "." in email.split("@")[1]

    @staticmethod
    def is_strong_password(password: str) -> bool:
        """Check if password is strong."""
        return (
            len(password) >= 8
            and any(c.isupper() for c in password)
            and any(c.islower() for c in password)
            and any(c.isdigit() for c in password)
        )

    @staticmethod
    def is_valid_age(age: int) -> bool:
        """Validate age range."""
        return 0 <= age <= 150


class DateUtils:
    """Date-related utilities."""

    @staticmethod
    def is_leap_year(year: int) -> bool:
        """Check if year is a leap year."""
        return year % 4 == 0 and (year % 100 != 0 or year % 400 == 0)

    @staticmethod
    def days_in_month(month: int, year: int) -> int:
        """Get number of days in a month."""
        if month in [1, 3, 5, 7, 8, 10, 12]:
            return 31
        elif month in [4, 6, 9, 11]:
            return 30
        else:  # February
            return 29 if DateUtils.is_leap_year(year) else 28


if __name__ == "__main__":
    print("=== StringUtils ===")
    # Can call without creating an instance
    print(f"Is 'racecar' palindrome? {StringUtils.is_palindrome('racecar')}")
    print(f"Is 'hello' palindrome? {StringUtils.is_palindrome('hello')}")
    print(f"Capitalize: {StringUtils.capitalize_words('hello world python')}")
    print(f"Vowels in 'education': {StringUtils.count_vowels('education')}")

    print("\n=== MathUtils ===")
    print(f"Is 17 prime? {MathUtils.is_prime(17)}")
    print(f"Is 20 prime? {MathUtils.is_prime(20)}")
    print(f"Factorial of 5: {MathUtils.factorial(5)}")
    print(f"25°C = {MathUtils.celsius_to_fahrenheit(25):.1f}°F")

    print("\n=== Validator ===")
    print(f"Valid email 'user@example.com'? {Validator.is_valid_email('user@example.com')}")
    print(f"Valid email 'invalid'? {Validator.is_valid_email('invalid')}")
    print(f"Strong password 'Pass123'? {Validator.is_strong_password('Pass123')}")
    print(f"Strong password 'Password123'? {Validator.is_strong_password('Password123')}")

    print("\n=== DateUtils ===")
    print(f"Is 2024 leap year? {DateUtils.is_leap_year(2024)}")
    print(f"Is 2025 leap year? {DateUtils.is_leap_year(2025)}")
    print(f"Days in Feb 2024: {DateUtils.days_in_month(2, 2024)}")

    # Static methods can also be called on instances (but not common)
    utils = StringUtils()
    print(f"\nCalling on instance: {utils.is_palindrome('noon')}")
