# """
# Example demonstrating the behavior of class variables in Python,
# especially the difference between mutable and immutable types.
# """    
# class Demo:
#     counter = 0      # Immutable class variable
#     items = []       # Mutable class variable
#     def __init__(self, name: str = "") -> None:
#         # counter +=1
#         self.name = name
# 
# d1 = Demo('d1')
# d2 = Demo('d2')
# 
# # Case 1: Reassignment - creates instance variable
# print("Before reassignment:")
# print(f"d1.counter: {d1.counter}, d2.counter: {d2.counter}, Demo.counter: {Demo.counter}")
# 
# d1.counter = 5  # Creates instance variable on d1
# print("After d1.counter = 5:")
# print(f"d1.counter: {d1.counter}, d2.counter: {d2.counter}, Demo.counter: {Demo.counter}")
# 
# # Case 2: In-place modification - affects all instances
# print("\nBefore in-place modification:")
# print(f"d1.items: {d1.items}, d2.items: {d2.items}")
# 
# d1.items.append('a')  # Modifies the shared list
# print("After d1.items.append('a'):")
# print(f"d1.items: {d1.items}, d2.items: {d2.items}, Demo.items: {Demo.items}")
# 
# # Case 3: Modifying via class - affects all
# print("\nModifying via class:")
# Demo.counter = 100
# print(f"d1.counter: {d1.counter} (has instance var), d2.counter: {d2.counter} (uses class var)")
# 
# Demo.items.append('b')
# print(f"d1.items: {d1.items}, d2.items: {d2.items}")
# 
# 
# print("\n=== Counter Example: Track Active Instances ===")

class TrackedObject:
    """Track the number of active instances."""
    active_count = 0  # Class variable to track instances
    
    def __init__(self, name: str) -> None:
        self.name = name
        TrackedObject.active_count += 1  # Increment on creation
        print(f"Created {self.name}. Active instances: {TrackedObject.active_count}")
    
    def __del__(self) -> None:
        """Called when instance is about to be destroyed."""
        TrackedObject.active_count -= 1  # Decrement on deletion
        print(f"Deleted {self.name}. Active instances: {TrackedObject.active_count}")
    
    @classmethod
    def get_count(cls) -> int:
        return cls.active_count


# Create instances
obj1 = TrackedObject("obj1")
obj2 = TrackedObject("obj2")
obj3 = TrackedObject("obj3")

print(f"\nTotal active: {TrackedObject.get_count()}")

# Delete an instance
del obj2
print(f"After deleting obj2: {TrackedObject.get_count()}")

print("\nModifying instance variable vs class variable:")
obj1.active_count = 50  # Creates instance variable on obj1
print(f"obj1.active_count (instance var): {obj1.active_count}")
print(f"TrackedObject.active_count (class var): {TrackedObject.active_count}")
print(f"obj3.active_count (uses class var): {obj3.active_count}")

print("\nReverting instance variable back to class variable:")
del obj1.active_count  # Remove instance variable
print(f"After 'del obj1.active_count':")
print(f"obj1.active_count: {obj1.active_count} (now uses class variable again)")

print("\n>>> Script ending - Python will clean up remaining objects (obj1, obj3)...")
# When script exits, obj1 and obj3 are automatically garbage collected
