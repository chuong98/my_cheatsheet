"""
    MRO (Method Resolution Order) in Python determines the order in which base classes are searched when executing a method.
"""

class A:
    def who_am_i(self):
        return "I am A"
    def do_something(self):
        return "Doing something in A"
class B(A):
    def who_am_i(self):
        return "I am B"
    def do_something(self):
        return super().do_something() + " and B"

# class C(A,B): # this will cause MRO conflict, since B is inherited from A, so A appears twice in the hierarchy. B must come before A.
class C(B,A):
    def who_am_i(self):
        return "I am C"
    def do_something(self):
        return super().do_something() + " and C"
    

c = C()
print(c.who_am_i())  # I am A
print(c.do_something())  # Doing something in A and B and C