
from src.model.scenarios.geometry import Coord
from src.model.scenarios.select_strategy import SelectStrategy


class AllSelectStrategy(SelectStrategy):
    def select(self, figures: list, click: Coord) -> list:
        ans = []

        for figure in figures:
            if figure.shoot(click):
                ans.append(figure)

        return ans