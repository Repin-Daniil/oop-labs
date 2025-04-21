from src.domain.objects.circle import Circle
from src.domain.objects.ellipse import Ellipse
from src.domain.objects.rectangle import Rectangle
from src.domain.objects.square import Square
from src.domain.objects.triangle import Triangle
from src.domain.visitor import Visitor
from typing import Optional

from src.model.model_object import ModelObject


class ColorVisitor(Visitor):
    def __init__(self, new_color: Optional[tuple[int, int, int]] = None):
        self.new_color = new_color
        self.old_color: Optional[tuple[int, int, int]] = None


    def change_color(self, shape:ModelObject):
        if self.new_color is not None:
            self.old_color = shape.color
            shape.color = self.new_color
        else:
            self.old_color = shape.color

    def visit_circle(self, circle: Circle):
        self.change_color(circle)

    def visit_rectangle(self, rectangle: Rectangle):
        self.change_color(rectangle)

    def visit_triangle(self, triangle: Triangle):
     self.change_color(triangle)

    def visit_square(self, square: Square):
        self.change_color(square)

    def visit_ellipse(self, ellipse: Ellipse):
        self.change_color(ellipse)

