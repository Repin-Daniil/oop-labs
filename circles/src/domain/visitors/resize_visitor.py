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

