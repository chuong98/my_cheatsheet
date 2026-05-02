"""
Your application has grown in complexity, and manually injecting dependencies into each class is becoming unmanageable. 
You need a more scalable solution for dependency injection.
To address this, you can implement a simple Dependency Injection (DI) framework that automatically resolves and injects dependencies based on type hints.
"""
from dependency_injector import containers, providers
from abc import ABC, abstractmethod
class Database(ABC): ...

class SQLDatabase(Database):
    def connect(self):
        pass

class UserService:
    def __init__(self, db: Database):
        print ("UserService initialized with db:", db)
        self.db = db


class Container(containers.DeclarativeContainer):
    # Map the Database abstraction to a concrete SQL implementation
    db = providers.Singleton(SQLDatabase)
    
    # Automatically inject 'db' into UserService
    user_service = providers.Factory(UserService, db=db)

# Usage
container = Container()
service = container.user_service() # The container builds the whole tree for you