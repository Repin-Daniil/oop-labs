from src.domain.objects.rectangle import Rectangle
from src.domain.objects.triangle import Triangle
from src.domain.visitor import Visitor
from src.model.scenarios.geometry import normalize_figure, Coord


class ResizeVisitor(Visitor):
    def __init__(self, step: int, canvas_width: int, canvas_height: int):
        self.step = step
        self.canvas_width = canvas_width
        self.canvas_height = canvas_height

    def visit_circle(self, circle):
        circle.radius  = max(10, min(200, circle.radius + self.step))
        dx, dy = normalize_figure(self.canvas_width, self.canvas_height, circle.get_bounding_box())
        circle.center += Coord(dx, dy)

    def visit_rectangle(self, rectangle: Rectangle):
        # Изменяем размеры прямоугольника, сохраняя минимальные и максимальные ограничения
        rectangle.width = max(10, min(200, rectangle.width + self.step))
        rectangle.height = max(10, min(200, rectangle.height + self.step))
        dx, dy = normalize_figure(self.canvas_width, self.canvas_height, rectangle.get_bounding_box())
        rectangle.top_left += Coord(dx, dy)
        return rectangle

    # def visit_triangle(self, triangle: Triangle):
    #     # Масштабируем треугольник относительно его центра
    #     center = triangle.get_center()
    #
    #     def scale_point(pt: Coord) -> Coord:
    #         # Масштаб: изменение на процентное соотношение self.step (например, 10 означает увеличение на 10%)
    #         factor = 1 + (self.step / 100)
    #         return Coord(
    #             int(center.x + (pt.x - center.x) * factor),
    #             int(center.y + (pt.y - center.y) * factor)
    #         )
    #
    #     triangle.p1 = scale_point(triangle.p1)
    #     triangle.p2 = scale_point(triangle.p2)
    #     triangle.p3 = scale_point(triangle.p3)
    #     dx, dy = normalize_figure(self.canvas_width, self.canvas_height, triangle.get_bounding_box())
    #     triangle.p1 += Coord(dx, dy)
    #     triangle.p2 += Coord(dx, dy)
    #     triangle.p3 += Coord(dx, dy)
    #     return triangle