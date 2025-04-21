from abc import ABC, abstractmethod

from src.domain.objects.circle import Circle
from src.domain.objects.ellipse import Ellipse
from src.domain.objects.rectangle import Rectangle
from src.domain.objects.square import Square
from src.domain.objects.triangle import Triangle


class Visitor(ABC):
    @abstractmethod
    def visit_circle(self, circle: Circle):
        pass

    @abstractmethod
    def visit_rectangle(self, rectangle: Rectangle):
        pass

    @abstractmethod
    def visit_triangle(self, triangle: Triangle):
        pass

    @abstractmethod
    def visit_square(self, square: Square):
        pass

    @abstractmethod
    def visit_ellipse(self, ellipse: Ellipse):
        pass



    # @abstractmethod
    # def visit_group(self, group: Group):
    #     pass
