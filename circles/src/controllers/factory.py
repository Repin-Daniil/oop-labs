from abc import ABC, abstractmethod

from src.model.model_object import ModelObject
from src.model.scenarios.geometry import Coord


class ObjectFactory(ABC):
    @abstractmethod
    def create_object(self, obj_type, coord : Coord, object_id: int | None, size : int, color) -> ModelObject:
        pass


