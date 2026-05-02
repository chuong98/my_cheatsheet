"""
The Observer pattern defines a one-to-many dependency.
When one object (the Subject) changes state, all its dependents (Observers) are notified automatically
"""
from abc import ABC, abstractmethod

class Subject:
    def __init__(self):
        self._observers = []
        self._state = None

    def attach(self, observer):
        self._observers.append(observer)

    def detach(self, observer):
        self._observers.remove(observer)

    def notify(self):
        for observer in self._observers:
            observer.update(self._state)

    def set_state(self, state):
        self._state = state
        self.notify()

class Observer(ABC):
    @abstractmethod
    def update(self, state):
        pass

class ConcreteObserverA(Observer):
    def update(self, state):
        print(f"ConcreteObserverA: Reacted to state change to {state}")

class ConcreteObserverB(Observer):
    def update(self, state):
        print(f"ConcreteObserverB: Reacted to state change to {state}")
# Example usage
if __name__ == "__main__":
    subject = Subject()

    observer_a = ConcreteObserverA()
    observer_b = ConcreteObserverB()

    subject.attach(observer_a)
    subject.attach(observer_b)

    print("Setting state to 'State 1' will notify all observers")
    subject.set_state("State 1")

    print("\nDetaching ConcreteObserverA")
    subject.detach(observer_a)

    print("Setting state to 'State 2' will notify the remaining observers")
    subject.set_state("State 2")