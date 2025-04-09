from src.controllers.factory import ObjectFactory
from src.domain.objects.circle import Circle

from src.model.model_object import ModelObject
from src.model.scenarios.geometry import Coord, normalize_figure


class StandardFactory(ObjectFactory):
    def create_object(self, obj_type, coord: Coord, object_id: int | None, canvas_width, canvas_height, size=10, color=(0, 0, 0)) -> ModelObject:
        if obj_type == "circle":
            circle =  Circle(coord, size, object_id, color)

            dx, dy = normalize_figure(canvas_width, canvas_height, circle.get_bounding_box())
            circle.center += Coord(dx, dy)

            return circle
        # elif obj_type == "quad":
        #     return Quad(x, y, size, color, selected)
        # elif name == "triangle":
        #     return Triangle(x, y, size, color, selected)
        #