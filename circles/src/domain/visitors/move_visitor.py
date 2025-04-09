from src.domain.objects.circle import Circle
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