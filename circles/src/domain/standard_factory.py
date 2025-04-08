from src.controllers.factory import ObjectFactory
from src.domain.objects.circle import Circle

from src.model.model_object import ModelObject
from src.model.scenarios.geometry import Coord


class StandardFactory(ObjectFactory):
    def create_object(self, obj_type, coord: Coord, object_id: int | None, size=10, color=(0, 0, 0)) -> ModelObject:
        if obj_type == "circle":
            return Circle(coord, size, object_id, color)
        # elif obj_type == "quad":
        #     return Quad(x, y, size, color, selected)
        # elif name == "triangle":
        #     return Triangle(x, y, size, color, selected)
        #