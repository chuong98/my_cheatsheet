class D:
    def do_work(self):
        print("Final processing in D")

class A(D):
    def do_work(self):
        print("Action in A")
        super().do_work()

class B(D):
    def do_work(self):
        print("Action in B")
        super().do_work()

class C(A, B):
    def do_work(self):
        print("Starting in C")
        super().do_work()

c = C()
print([cls.__name__ for cls in C.mro()])
c.do_work()

"""
When you call C().do_work(), Python looks at the __mro__ attribute of the class. 
For the structure above, the order is: C → A → B → D → object.
- The "Double Call" Problem: 
    If you used direct calls like A.do_work(self) and B.do_work(self) inside class C, 
    the method in class D would be executed twice.
- The super() Solution: When A calls super().do_work(), it doesn't necessarily call its direct parent (D). 
    Instead, it looks at the MRO of the object that started the call (C) and sees that B is next. So, it calls B's do_work().
    Then, when B calls super().do_work(), it sees that D is next in the MRO and calls D's do_work().
    This ensures a linear path through the entire "diamond."
"""