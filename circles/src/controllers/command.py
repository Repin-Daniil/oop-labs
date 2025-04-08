from abc import ABC, abstractmethod
from typing import List

from src.model.model_object import ModelObject

class Command(ABC):
    @abstractmethod
    def execute(self, objects: List[ModelObject]):
       pass

    @abstractmethod
    def undo(self):
       pass

    @abstractmethod
    def redo(self):
        pass

    @abstractmethod
    def clone(self):
        pass
