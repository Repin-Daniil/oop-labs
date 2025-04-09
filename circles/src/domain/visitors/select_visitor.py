from src.domain.objects.rectangle import Rectangle
from src.domain.objects.triangle import Triangle
from src.domain.visitor import Visitor


class SelectVisitor(Visitor):
    def visit_circle(self, circle: 'Circle'):
        circle.selected = not circle.selected

    def visit_rectangle(self, rectangle: Rectangle):
        rectangle.selected = not rectangle.selected
    #
    # def visit_triangle(self, triangle: Triangle):
    #     triangle.selected = not triangle.selected

