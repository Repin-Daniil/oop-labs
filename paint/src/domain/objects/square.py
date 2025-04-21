from typing import Tuple

from src.model.model_object import ModelObject
from src.model.scenarios.geometry import Coord


class Square(ModelObject):
    def __init__(self, top_left: Coord, side_length: int, figure_id: int | None, color=(0, 0, 0)):
        super().__init__(figure_id)
        self.top_left = top_left
        self.side_length = side_length
        self.color = color
        self.selected = False

    def accept(self, visitor: 'Visitor'):
        visitor.visit_square(self)

    def shoot(self, click: Coord) -> bool:
        return (self.top_left.x <= click.x <= self.top_left.x + self.side_length and
                self.top_left.y <= click.y <= self.top_left.y + self.side_length)

    def get_bounding_box(self) -> Tuple[int, int, int, int]:
        left = self.top_left.x
        right = self.top_left.x + self.side_length
        top = self.top_left.y
        bottom = self.top_left.y + self.side_length
        return left, right, top, bottom

    def get_color(self) -> tuple[int, int, int]:
        return self.color

    def get_top_left(self) -> Coord:
        return self.top_left

    def get_side_length(self) -> int:
        return self.side_length

    def get_name(self, num_id):
        return "Square " + str(num_id)

    def is_selected(self) -> bool:
        return self.selected