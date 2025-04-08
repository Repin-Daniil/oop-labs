
from src.model.scenarios.geometry import Coord
from src.model.scenarios.select_strategy import SelectStrategy


class ConquerWorldStrategy(SelectStrategy):
    def select(self, figures: list, click: Coord) -> list:
        return figures