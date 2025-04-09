from src.controllers.factory import ObjectFactory
from src.domain.objects.circle import Circle
from src.domain.objects.rectangle import Rectangle
from src.domain.objects.triangle import Triangle

from src.model.model_object import ModelObject
from src.model.scenarios.geometry import Coord, normalize_figure


class StandardFactory(ObjectFactory):
    def create_object(self, obj_type, coord: Coord, object_id: int | None, canvas_width, canvas_height, size=10, color=(0, 0, 0)) -> ModelObject:
        if obj_type == "circle":
            circle =  Circle(coord, size, object_id, color)

            dx, dy = normalize_figure(canvas_width, canvas_height, circle.get_bounding_box())
            circle.center += Coord(dx, dy)

            return circle


        elif obj_type == "rectangle":
            # Для прямоугольника используем координату как верхний левый угол.
            rectangle = Rectangle(coord, size, size, object_id, color)
            dx, dy = normalize_figure(canvas_width, canvas_height, rectangle.get_bounding_box())
            rectangle.top_left += Coord(dx, dy)
            return rectangle

        # elif obj_type == "triangle":
        #     # Создаем равнобедренный треугольник, где coord является левой вершиной основания.
        #     p1 = coord
        #     p2 = coord + Coord(size, 0)
        #     # Вторая вершина базируется на размере (можно менять параметры для более сложного поведения)
        #     p3 = coord + Coord(size // 2, size)
        #     triangle = Triangle(p1, p2, p3, object_id, color)
        #     dx, dy = normalize_figure(canvas_width, canvas_height, triangle.get_bounding_box())
        #     triangle.p1 += Coord(dx, dy)
        #     triangle.p2 += Coord(dx, dy)
        #     triangle.p3 += Coord(dx, dy)
        #     return triangle

        else:
            raise ValueError("Неизвестный тип объекта: " + str(obj_type))

