from abc import ABC, abstractmethod

"""
TWO DIFFERENT CONCEPTS:

1. Registry Pattern (using __init_subclass__):
   - Custom pattern to track and create subclasses dynamically
   - Stores subclasses in a dictionary for factory creation

"""

print("="*60)
print("1. CUSTOM REGISTRY PATTERN (using __init_subclass__)")
print("="*60)

class PluginRegistry(ABC):
    """Base class with automatic subclass registration."""
    
    _registry = {}  # Class variable to store registered plugins
    
    def __init_subclass__(cls, **kwargs):
        """Automatically called when a subclass is created."""
        super().__init_subclass__(**kwargs)
        # Register the subclass using its name as key
        cls._registry[cls.__name__.lower()] = cls
        print(f"Registered plugin: {cls.__name__}")
    
    @classmethod
    def create(cls, plugin_name: str, *args, **kwargs):
        """Factory method to create plugin instances by name."""
        plugin_class = cls._registry.get(plugin_name.lower())
        if plugin_class is None:
            raise ValueError(f"Unknown plugin: {plugin_name}")
        return plugin_class(*args, **kwargs)
    
    @classmethod
    def list_plugins(cls):
        """List all registered plugins."""
        return list(cls._registry.keys())
    
    @abstractmethod
    def execute(self):
        """Each plugin must implement this method."""
        pass


# Plugins are automatically registered when defined
class EmailPlugin(PluginRegistry):
    """Plugin for sending emails."""
    
    def __init__(self, recipient: str):
        self.recipient = recipient
    
    def execute(self):
        return f"Sending email to {self.recipient}"


class SmsPlugin(PluginRegistry):
    """Plugin for sending SMS."""
    
    def __init__(self, phone: str):
        self.phone = phone
    
    def execute(self):
        return f"Sending SMS to {self.phone}"


class PushPlugin(PluginRegistry):
    """Plugin for push notifications."""
    
    def __init__(self, device_id: str):
        self.device_id = device_id
    
    def execute(self):
        return f"Sending push notification to device {self.device_id}"


# Example usage
print("\nAvailable plugins:", PluginRegistry.list_plugins())

# Create plugins using factory method
email = PluginRegistry.create("emailplugin", "user@example.com")
sms = PluginRegistry.create("smsplugin", "+1234567890")
push = PluginRegistry.create("pushplugin", "device-abc123")

print(f"\n{email.execute()}")
print(f"{sms.execute()}")
print(f"{push.execute()}")

# Dynamic plugin creation based on user input
plugin_type = "emailplugin"  # Could come from config or user input
plugin = PluginRegistry.create(plugin_type, "admin@example.com")
print(f"\nDynamically created: {plugin.execute()}")



