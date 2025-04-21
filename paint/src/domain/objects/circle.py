from math import hypot
from typing import Tuple

from src.model.scenarios.geometry import Coord
from src.model.model_object import ModelObject


class Circle(ModelObject):
    def __init__(self, center : Coord, radius : int, figure_id: int | None, color=(0, 0, 0)):
        super().__init__(figure_id)
        self.center = center
        self.radius = radius
        self.color = color
        self.selected = False

    def accept(self, visitor: 'Visitor'):
        visitor.visit_circle(self)

    def shoot(self, click: Coord) -> bool:
        return hypot(click.x - self.center.x, click.y - self.center.y) <= self.radius

    def get_bounding_box(self) -> Tuple[int, int, int, int]:
        left = self.center.x - self.radius
        right = self.center.x + self.radius
        top = self.center.y - self.radius
        bottom = self.center.y + self.radius

        return left, right, top, bottom

    def get_color(self) -> tuple[int, int, int]:
        return self.color

    def get_center(self) -> Coord:
        return self.center

    def get_radius(self) -> int:
        return self.radius

    def get_name(self, num_id):
        return "Circle " + str(num_id)

    def is_selected(self) -> bool:
        return self.selected