from src.domain.objects.circle import Circle
from src.domain.objects.rectangle import Rectangle
from src.domain.objects.triangle import Triangle
from src.domain.visitor import Visitor
from src.model.scenarios.geometry import Coord, normalize_figure


class MoveVisitor(Visitor):
    def __init__(self, dx: int, dy: int, canvas_width: int, canvas_height: int):
        self.dx = dx
        self.dy = dy
        self.canvas_width = canvas_width
        self.canvas_height = canvas_height

    def visit_circle(self, circle: Circle):
        circle.center = circle.get_center() + Coord(self.dx, self.dy)
        dx, dy = normalize_figure(self.canvas_width, self.canvas_height, circle.get_bounding_box())
        circle.center += Coord(dx, dy)

    def visit_rectangle(self, rectangle: Rectangle):
        rectangle.top_left = rectangle.top_left + Coord(self.dx, self.dy)
        dx, dy = normalize_figure(self.canvas_width, self.canvas_height, rectangle.get_bounding_box())
        rectangle.top_left += Coord(dx, dy)
        return rectangle
    #
    # def visit_triangle(self, triangle: Triangle):
    #     triangle.p1 = triangle.p1 + Coord(self.dx, self.dy)
    #     triangle.p2 = triangle.p2 + Coord(self.dx, self.dy)
    #     triangle.p3 = triangle.p3 + Coord(self.dx, self.dy)
    #     dx, dy = normalize_figure(self.canvas_width, self.canvas_height, triangle.get_bounding_box())
    #     triangle.p1 += Coord(dx, dy)
    #     triangle.p2 += Coord(dx, dy)
    #     triangle.p3 += Coord(dx, dy)
    #     return triangle