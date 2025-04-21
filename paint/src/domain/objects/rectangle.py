from typing import Tuple

from src.model.model_object import ModelObject
from src.model.scenarios.geometry import Coord


class Rectangle(ModelObject):
    def __init__(self, top_left: Coord, width: int, height: int, figure_id: int | None, color=(0, 0, 0)):
        super().__init__(figure_id)
        self.top_left = top_left
        self.width = width
        self.height = height
        self.color = color
        self.selected = False

    def accept(self, visitor: 'Visitor'):
        visitor.visit_rectangle(self)

    def shoot(self, click: Coord) -> bool:
        return (self.top_left.x <= click.x <= self.top_left.x + self.width and
                self.top_left.y <= click.y <= self.top_left.y + self.height)

    def get_bounding_box(self) -> Tuple[int, int, int, int]:
        left = self.top_left.x
        right = self.top_left.x + self.width
        top = self.top_left.y
        bottom = self.top_left.y + self.height

        return left, right, top, bottom

    def get_color(self) -> tuple[int, int, int]:
        return self.color

    def get_center(self) -> Coord:
        cx = self.top_left.x + self.width // 2
        cy = self.top_left.y + self.height // 2
        return Coord(cx, cy)

    def get_width(self) -> int:
        return self.width

    def get_height(self) -> int:
        return self.height

    def get_name(self, num_id):
        return "Rectangle " + str(num_id)

    def is_selected(self) -> bool:
        return self.selected
