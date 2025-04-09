from typing import Tuple

from src.model.model_object import ModelObject
from src.model.scenarios.geometry import Coord


class Ellipse(ModelObject):
    def __init__(self, center: Coord, radius_x: int, radius_y: int, figure_id: int | None, color=(0, 0, 0)):
        super().__init__(figure_id)
        self.center = center
        self.radius_x = radius_x
        self.radius_y = radius_y
        self.color = color
        self.selected = False

    def accept(self, visitor: 'Visitor'):
        visitor.visit_ellipse(self)

    def shoot(self, click: Coord) -> bool:
        return ((click.x - self.center.x) ** 2) / (self.radius_x ** 2) + ((click.y - self.center.y) ** 2) / (self.radius_y ** 2) <= 1

    def get_bounding_box(self) -> Tuple[int, int, int, int]:
        left = self.center.x - self.radius_x
        right = self.center.x + self.radius_x
        top = self.center.y - self.radius_y
        bottom = self.center.y + self.radius_y
        return left, right, top, bottom

    def get_color(self) -> tuple[int, int, int]:
        return self.color

    def get_center(self) -> Coord:
        return self.center

    def get_radius_x(self) -> int:
        return self.radius_x

    def get_radius_y(self) -> int:
        return self.radius_y

    def get_name(self, num_id):
        return "Ellipse " + str(num_id)

    def is_selected(self) -> bool:
        return self.selected
