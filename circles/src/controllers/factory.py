from abc import ABC, abstractmethod

from src.model.model_object import ModelObject
from src.model.scenarios.geometry import Coord


class ObjectFactory(ABC):
    @abstractmethod
    def create_object(self, obj_type, coord: Coord, object_id: int | None, canvas_width, canvas_height, size=10, color=(0, 0, 0)) -> ModelObject:
        pass


