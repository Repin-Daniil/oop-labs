from abc import ABC, abstractmethod

from src.model.scenarios.geometry import Coord


class SelectStrategy(ABC):
    @abstractmethod
    def select(self, figures: list, click: Coord) -> list:
        pass
