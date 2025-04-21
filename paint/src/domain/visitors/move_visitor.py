from src.domain.objects.circle import Circle
from src.domain.objects.ellipse import Ellipse
from src.domain.objects.rectangle import Rectangle
from src.domain.objects.square import Square
from src.domain.objects.triangle import Triangle
from src.domain.visitor import Visitor
from src.model.scenarios.geometry import Coord, normalize_figure


class MoveVisitor(Visitor):
    def __init__(self, delta:Coord, canvas_width: int, canvas_height: int):
        self.delta = delta
        self.canvas_width = canvas_width
        self.canvas_height = canvas_height

    def visit_circle(self, circle: Circle):
        circle.center = circle.get_center() + self.delta
        dx, dy = normalize_figure(self.canvas_width, self.canvas_height, circle.get_bounding_box())
        circle.center += Coord(dx, dy)
        self.delta += Coord(dx, dy)


    def visit_rectangle(self, rectangle: Rectangle):
        rectangle.top_left = rectangle.top_left + self.delta
        dx, dy = normalize_figure(self.canvas_width, self.canvas_height, rectangle.get_bounding_box())
        rectangle.top_left += Coord(dx, dy)
        self.delta += Coord(dx, dy)


    def visit_triangle(self, triangle: Triangle):
        triangle.p1 = triangle.p1 + self.delta
        triangle.p2 = triangle.p2 + self.delta
        triangle.p3 = triangle.p3 + self.delta
        dx, dy = normalize_figure(self.canvas_width, self.canvas_height, triangle.get_bounding_box())
        triangle.p1 += Coord(dx, dy)
        triangle.p2 += Coord(dx, dy)
        triangle.p3 += Coord(dx, dy)
        self.delta += Coord(dx, dy)

    def visit_square(self, square: Square):
        square.top_left = square.top_left + self.delta
        dx, dy = normalize_figure(self.canvas_width, self.canvas_height, square.get_bounding_box())
        square.top_left += Coord(dx, dy)
        self.delta += Coord(dx, dy)

    def visit_ellipse(self, ellipse: Ellipse):
        ellipse.center = ellipse.get_center() + self.delta
        dx, dy = normalize_figure(self.canvas_width, self.canvas_height, ellipse.get_bounding_box())
        ellipse.center += Coord(dx, dy)
        self.delta += Coord(dx, dy)

    def get_delta(self):
        return self.delta

    def set_delta(self, delta: Coord):
        self.delta = delta