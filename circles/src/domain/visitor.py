from abc import ABC, abstractmethod

from src.domain.objects.circle import Circle


class Visitor(ABC):
    @abstractmethod
    def visit_circle(self, circle: Circle):
        pass

    # @abstractmethod
    # def visit_group(self, group: Group):
    #     pass