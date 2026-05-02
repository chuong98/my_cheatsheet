"""
You are developing a Python application that creates complex object graphs with cyclic references.
 Over time, you notice the application's memory usage keeps increasing. 
 What would you do to ensure proper garbage collection of these cyclic references?

1. What are Cyclic References?
A cyclic reference occurs when two or more objects refer to each other, creating a loop. 
Because each object holds a reference to the next, their reference counts never drop to zero, 
even if they are no longer accessible from the rest of your program.
"""

# example of cyclic references
class Node:
    def __init__(self, value):
        self.value = value
        self.next = None

node1 = Node(1)
node2 = Node(2)
node1.next = node2
node2.next = node1  # creates a cycle
# Delete the variables from the local scope
del node1   
del node2
# The objects still exist in memory because they point to each other!

# 2. How to Handle Cyclic References?
# Python's garbage collector can handle cyclic references, but you can also use weak references to avoid them.
import weakref

class WeakRefNode:
    def __init__(self):
        self._child = None

    @property
    def child(self):
        return self._child() if self._child else None

    @child.setter
    def child(self, obj):
        # Store as a weak reference
        self._child = weakref.ref(obj)

nodeA = WeakRefNode()
nodeB = WeakRefNode()
nodeA.child = nodeB
nodeB.child = nodeA  # creates a cycle with weak references
# Delete the variables from the local scope
del nodeA   
del nodeB
# Now the objects can be garbage collected since they only hold weak references to each other.

# 3. Forcing Garbage Collection
# """
# If you are creating thousands of cyclic objects in a tight loop, the GC might not trigger frequently enough. You can force a collection manually.
# """
import gc
gc.collect()  # Force garbage collection to clean up cyclic referencessd