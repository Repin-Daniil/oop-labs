from src.model.actions.visitor import Visitor
from src.model.scenarios.geometry import Coord
from src.core.objects.circle import Circle


class MoveVisitor(Visitor):
    def __init__(self, dx: int, dy: int):
        self.dx = dx
        self.dy = dy

    def visit_circle(self, circle: Circle):
        new_center = circle.get_center() + Coord(self.dx, self.dy)
        circle.set_center(new_center)