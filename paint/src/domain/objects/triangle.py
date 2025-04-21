from typing import Tuple

from src.model.model_object import ModelObject
from src.model.scenarios.geometry import Coord


class Triangle(ModelObject):
    def __init__(self, p1: Coord, p2: Coord, p3: Coord, figure_id: int | None, color=(0, 0, 0)):
        super().__init__(figure_id)
        self.p1 = p1
        self.p2 = p2
        self.p3 = p3
        self.color = color
        self.selected = False

    def accept(self, visitor: 'Visitor'):
        visitor.visit_triangle(self)

    def shoot(self, click: Coord) -> bool:
        def area(a: Coord, b: Coord, c: Coord) -> float:
            return abs((a.x * (b.y - c.y) +
                        b.x * (c.y - a.y) +
                        c.x * (a.y - b.y)) / 2)

        total = area(self.p1, self.p2, self.p3)
        a1 = area(click, self.p2, self.p3)
        a2 = area(self.p1, click, self.p3)
        a3 = area(self.p1, self.p2, click)

        return abs(a1 + a2 + a3 - total) < 1e-5  # допускаем небольшую погрешность

    def get_bounding_box(self) -> Tuple[int, int, int, int]:
        xs = [self.p1.x, self.p2.x, self.p3.x]
        ys = [self.p1.y, self.p2.y, self.p3.y]
        return min(xs), max(xs), min(ys), max(ys)

    def get_color(self) -> tuple[int, int, int]:
        return self.color

    def get_center(self) -> Coord:
        cx = (self.p1.x + self.p2.x + self.p3.x) // 3
        cy = (self.p1.y + self.p2.y + self.p3.y) // 3
        return Coord(cx, cy)

    def get_points(self) -> Tuple[Coord, Coord, Coord]:
        return self.p1, self.p2, self.p3

    def get_name(self, num_id):
        return "Triangle " + str(num_id)

    def is_selected(self) -> bool:
        return self.selected
