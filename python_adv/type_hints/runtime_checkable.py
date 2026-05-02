from typing import Protocol, runtime_checkable

@runtime_checkable
class Drawable(Protocol):
    def draw(self) -> None:
        ...

class Circle:
    def draw(self) -> None:
        print("Drawing a circle")

class Radio:
    def play_music(self) -> None:
        print("Music playing")

# Verification
c = Circle()
r = Radio()

# Protocols allow structural subtyping (duck typing) without explicit inheritance
print(isinstance(c, Drawable))  # True: Circle has a 'draw' method, even without explicit inheritance from the Drawable class
print(isinstance(r, Drawable))  # False: Radio does not have 'draw', so it's not considered Drawable