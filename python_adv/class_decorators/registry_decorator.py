# Create a registry using a decorator
class HandlerRegistry:
    """Registry that uses decorator to register classes."""
    _handlers = {}
    
    @classmethod
    def register(cls, name=None):
        """Decorator to register a handler class."""
        def decorator(handler_class):
            # Use provided name or class name
            key = name or handler_class.__name__.lower()
            cls._handlers[key] = handler_class
            print(f"Registered handler: {key}")
            return handler_class  # Return the class unchanged
        return decorator
    
    @classmethod
    def get(cls, name):
        """Get a handler class by name."""
        handler = cls._handlers.get(name.lower())
        if handler is None:
            raise ValueError(f"Unknown handler: {name}")
        return handler
    
    @classmethod
    def create(cls, name, *args, **kwargs):
        """Create a handler instance by name."""
        handler_class = cls.get(name)
        return handler_class(*args, **kwargs)
    
    @classmethod
    def list_handlers(cls):
        """List all registered handlers."""
        return list(cls._handlers.keys())


# Use the decorator to register classes
@HandlerRegistry.register()  # Uses class name by default
class JsonHandler:
    def __init__(self, data):
        self.data = data
    
    def process(self):
        return f"Processing JSON: {self.data}"


@HandlerRegistry.register("xml")  # Custom name
class XmlHandler:
    def __init__(self, data):
        self.data = data
    
    def process(self):
        return f"Processing XML: {self.data}"


@HandlerRegistry.register("csv")
class CsvHandler:
    def __init__(self, data):
        self.data = data
    
    def process(self):
        return f"Processing CSV: {self.data}"


# Usage
print("\nAvailable handlers:", HandlerRegistry.list_handlers())

json_handler = HandlerRegistry.create("jsonhandler", {"key": "value"})
xml_handler = HandlerRegistry.create("xml", "<data>test</data>")
csv_handler = HandlerRegistry.create("csv", "a,b,c")

print(f"\n{json_handler.process()}")
print(f"{xml_handler.process()}")
print(f"{csv_handler.process()}")


print("\n" + "="*60)
print("3. FUNCTION REGISTRY (Bonus)")
print("="*60)

# You can also register functions, not just classes!
function_registry = {}

def register_function(name=None):
    """Decorator to register functions."""
    def decorator(func):
        key = name or func.__name__
        function_registry[key] = func
        print(f"Registered function: {key}")
        return func
    return decorator


@register_function("add")
def addition(a, b):
    return a + b


@register_function("multiply")
def multiplication(a, b):
    return a * b


@register_function()  # Uses function name
def subtract(a, b):
    return a - b


# Usage
print(f"\nAvailable functions: {list(function_registry.keys())}")
print(f"add(5, 3) = {function_registry['add'](5, 3)}")
print(f"multiply(5, 3) = {function_registry['multiply'](5, 3)}")
print(f"subtract(5, 3) = {function_registry['subtract'](5, 3)}")