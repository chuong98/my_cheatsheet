## 1. Definition

- In Python, a Metaclass is the "class of a class." While a standard class defines how an instance (object) behaves, a metaclass defines how the class itself behaves.
- If you think of a class as a blueprint for an object, a metaclass is the blueprint for the blueprint

## 2. How Metaclasses Work (The "Magic" Behind the Scenes)

In Python, everything is an object, including classes. Since every object must have a type, every class has a metaclass. By default, that metaclass is type.

When you define a class, Python executes the class body and then calls the metaclass to "build" the class object. By overriding the `__new__` or `__init__` methods of a metaclass, you can:

- Modify class attributes automatically.
- Enforce naming conventions.
- Register classes in a central database (as we saw with Django models).
- Prevent classes from being instantiated.

When writing a metaclass, you typically override these three methods:

| Method | Role | When to use |
|--------|------|-------------|
| `__new__` | Creates the class object. | Use this if you want to change the class (rename methods, add attributes). |
| `__init__` | Initializes the class object. | Use this if you just want to check or register the class after it's built. |
| `__call__` | Runs when the class is called to make an instance. | Use this for patterns like Singleton. |

## 3. Why use a Metaclass instead of a Decorator?

This is a common question. Class decorators are often easier to read, but metaclasses are more powerful because:

- Inheritance: Metaclasses are inherited by subclasses. If you decorate a base class, the decorator doesn't automatically apply to the children. A metaclass does.
- Early Intervention: Metaclasses run at the moment of class creation, allowing them to change the very structure of the class before it even exists in memory.

## 4. Using `__init_subclass__` for simpler syntax:

- for the vast majority of day-to-day coding tasks, __init_subclass__ (introduced in Python 3.6) can replace a Metaclass. It is much easier to read, doesn't require "deep magic" syntax, and plays nicely with multiple inheritance.

While a Metaclass controls the creation of the class, __init_subclass__ is a hook that runs automatically whenever a class is inherited.

### 4.1. Task: Automatic Class Registration

<table>
<tr>
<th>Metaclass Approach</th>
<th>__init_subclass__ Approach</th>
</tr>
<tr>
<td>

```python
class RegistryMeta(type):
    registry = []

    def __new__(mcs, name, bases, attrs):
        # Create the new class
        new_cls = super().__new__(mcs, name, bases, attrs)

        # Avoid registering a base class (optional logic)
        if not attrs.get('__abstract__'):
            RegistryMeta.registry.append(new_cls)

        return new_cls

class PluginBase(metaclass=RegistryMeta):
    __abstract__ = True

class AudioPlugin(PluginBase): pass
class VideoPlugin(PluginBase): pass

print(RegistryMeta.registry)
# [<class 'AudioPlugin'>, <class 'VideoPlugin'>]
```

</td>
<td>

```python
class PluginBase:
    registry = []

    def __init_subclass__(cls, **kwargs):
        super().__init_subclass__(**kwargs)
        # Automatically add the new subclass to our list
        PluginBase.registry.append(cls)

class AudioPlugin(PluginBase): pass
class VideoPlugin(PluginBase): pass

print(PluginBase.registry)
# [AudioPlugin, VideoPlugin]
```

</td>
</tr>
</table>

### 4.2 Task: Enforcing Class Attributes (Validation)
<table>
<tr>
<th>Metaclass Approach</th>
<th>__init_subclass__ Approach</th>
</tr>
<tr>
<td>

```python
class ValidationMeta(type):
    def __new__(mcs, name, bases, attrs):
        # We check the 'attrs' dictionary for our required key
        if name != "DatabaseModel" and "table_name" not in attrs:
            raise TypeError(f"Class {name} must define 'table_name'")
        
        return super().__new__(mcs, name, bases, attrs)

class DatabaseModel(metaclass=ValidationMeta):
    pass

# This works:
class User(DatabaseModel):
    table_name = "users"

# This raises a TypeError immediately when Python reads the file:
# class Product(DatabaseModel):
#     pass
```

</td>
<td>

```python
class DatabaseModel:
    def __init_subclass__(cls, table_name=None, **kwargs):
        super().__init_subclass__(**kwargs)
        if table_name is None:
            raise TypeError(f"Class {cls.__name__} must provide a 'table_name' argument")
        cls._table = table_name

# This works:
class User(DatabaseModel, table_name="users"):
    pass

# This raises a TypeError immediately:
# class Product(DatabaseModel): 
#     pass
```

</td>
</tr>
</table>

### 4.3. Task: Setting "Owner" Information
<table>
<tr>
<th>Metaclass Approach</th>
<th>__init_subclass__ Approach</th>
</tr>
<tr>
<td>

```python
class Field:
    def set_owner(self, owner_name):
        self.owner_name = owner_name

class OwnerMeta(type):
    def __new__(mcs, name, bases, attrs):
        new_cls = super().__new__(mcs, name, bases, attrs)
        
        # Look through attributes for Field instances
        for attr_name, attr_value in attrs.items():
            if isinstance(attr_value, Field):
                attr_value.set_owner(name)
                
        return new_cls

class Customer(metaclass=OwnerMeta):
    name = Field()

print(Customer.name.owner_name) # Output: Customer
```

</td>
<td>

```python
class Field:
    def __set_name__(self, owner, name):
        self.name = name

class Model:
    def __init_subclass__(cls, **kwargs):
        super().__init_subclass__(**kwargs)
        # You could perform logic here to link fields to the class
        print(f"Refining class: {cls.__name__}")

class Customer(Model):
    name = Field()
```

</td>
</tr>
</table>

## 4.4 Metaclass is required to do singleton class
``` python
import threading

class SingletonMeta(type):
    """
    A thread-safe implementation of Singleton.
    """
    _instances = {}
    _lock: threading.Lock = threading.Lock()

    def __call__(cls, *args, **kwargs):
        # First check (optimization): if the instance already exists, 
        # return it immediately without acquiring the lock.
        if cls not in cls._instances:
            # Acquire the lock to ensure only one thread creates the instance.
            with cls._lock:
                # Second check: once we have the lock, check again in case 
                # another thread created it while we were waiting.
                if cls not in cls._instances:
                    instance = super().__call__(*args, **kwargs)
                    cls._instances[cls] = instance
        return cls._instances[cls]

# Usage
class DatabaseConnection(metaclass=SingletonMeta):
    def __init__(self):
        self.connection_string = "Loaded"
        print("Initializing heavy database connection...")

# Simulating multithreaded access
def create_connection():
    db = DatabaseConnection()
    print(f"Database connection string: {db.connection_string}")
threads = []
for i in range(5):
    thread = threading.Thread(target=create_connection)
    threads.append(thread)
    thread.start()
for thread in threads:
    thread.join()
```