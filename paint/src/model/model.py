from typing import List

from src.model.scenarios.select_strategy import SelectStrategy
from src.model.scenarios.strategies.conquer_world import ConquerWorldStrategy
from src.model.scenarios.geometry import Coord
from src.model.model_object import ModelObject


class Model:
    def __init__(self, strategy: SelectStrategy):
        self.objects = []
        self.objects_dict = dict()
        self.select_strategy = strategy

    def add_figure(self, figure : ModelObject):
        self.objects_dict[figure.id] = figure
        self.objects.append(figure)

    def get_figure(self, figure_id : str) -> ModelObject | None:
        return self.objects_dict.get(figure_id)

    def remove_figure(self, object_id : str):
        self.objects_dict.pop(object_id)

        for figure in self.objects:
            if figure.id == object_id:
                self.objects.remove(figure)

    def select(self, click:Coord, select_all = False) -> List[ModelObject]:
        if select_all:
            return ConquerWorldStrategy().select(self.objects, click)

        return self.select_strategy.select(self.objects, click)

    def get_selected(self) -> List[ModelObject]:
        return [figure for figure in self.objects if figure.is_selected()]

    def set_select_policy(self, select_strategy: SelectStrategy):
        self.select_strategy = select_strategy

    def get_select_policy(self) -> SelectStrategy|None:
        return self.select_strategy