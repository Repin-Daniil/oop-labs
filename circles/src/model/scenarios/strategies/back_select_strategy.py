from src.model.scenarios.select_strategy import SelectStrategy
from src.model.scenarios.geometry import Coord

class BackSelectStrategy(SelectStrategy):
    def select(self, figures: list, click: Coord) -> list:
        for figure in reversed(figures):
            if figure.shoot(click):
                return [figure]

        return []