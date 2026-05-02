
They were promoted by Robert C. Martin (Uncle Bob) and have since become the industry standard for clean code.

1. `Single Responsibility Principle (SRP)`: "A class should have one, and only one, reason to change."
- A class should be responsible for only one part of the software's functionality. 
- If a class handles too many tasks (e.g., managing database connections and formatting reports), it becomes fragile. 
- If you change the database logic, you might accidentally break the report formatting.

2. `Open/Closed Principle (OCP)`:"Software entities should be open for extension, but closed for modification."
- You should be able to add new functionality to a class without changing its existing source code. This is typically achieved using inheritance or interfaces. 
- By doing this, you prevent bugs in existing, tested code while allowing the system to grow.

3. `Liskov Substitution Principle (LSP)`: "Subtypes must be substitutable for their base types."
- As we discussed with the Bird/Penguin example, if class B is a subclass of class A, you should be able to replace A with B without the program behaving unexpectedly. 
- A subclass should never "weaken" the behavior of the parent class (e.g., by throwing an error for a method the parent supports).

4. `Interface Segregation Principle (ISP)`: "Clients should not be forced to depend upon interfaces they do not use."
- It is better to have many small, specific interfaces than one large, "fat" interface. 
- If an interface has too many methods, classes implementing it are forced to write "dummy" code for methods they don't actually need.

5. `Dependency Inversion Principle (DIP)`: "Depend upon abstractions, not concretions."
- High-level modules (the logic) should not depend on low-level modules (the tools like databases or APIs). 
- Both should depend on abstractions (interfaces). 
- This makes it easy to swap out a low-level component (e.g., switching from a SQL database to a NoSQL one) without rewriting your entire business logic.

## Summary Table

| Name | Principle | Core Idea | Main Benefit |
|------|-----------|-----------|--------------|
| SRP | Single Responsibility | One class = One task | Easy to understand and debug |
| OCP | Open/Closed | Extend code, don't edit it | Prevents regression bugs |
| LSP | Liskov Substitution | Subclasses must "fit" the parent | Predictable behavior in hierarchies |
| ISP | Interface Segregation | Keep interfaces small | Reduces unnecessary code bloat |
| DIP | Dependency Inversion | Use interfaces to decouple code | Makes components easy to swap |
