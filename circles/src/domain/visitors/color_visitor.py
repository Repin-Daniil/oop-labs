from src.domain.objects.circle import Circle
from src.domain.objects.rectangle import Rectangle
from src.domain.objects.triangle import Triangle
from src.domain.visitor import Visitor
from typing import Optional


class ColorVisitor(Visitor):
    def __init__(self, new_color: Optional[tuple[int, int, int]] = None):
        self.new_color = new_color
        self.old_color: Optional[tuple[int, int, int]] = None

    def visit_circle(self, circle: Circle):
        if self.new_color is not None:
            self.old_color = circle.color
            circle.color = self.new_color
        else:
            self.old_color = circle.color

    def visit_rectangle(self, rectangle: Rectangle):
        if self.new_color is not None:
            self.old_color = rectangle.color
            rectangle.color = self.new_color
        else:
            self.old_color = rectangle.color

    def visit_triangle(self, triangle: Triangle):
        if self.new_color is not None:
            self.old_color = triangle.color
            triangle.color = self.new_color
        else:
            self.old_color = triangle.color



