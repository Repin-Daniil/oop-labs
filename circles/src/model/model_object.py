from abc import ABC, abstractmethod

from src.model.scenarios.geometry import Coord


class ModelObject(ABC):
    id_seq = {0}

    def __init__(self, figure_id : int | None) -> None:
        if figure_id and figure_id in ModelObject.id_seq:
            raise ValueError(f"Figure with id {figure_id} already exists")

        if figure_id is None:
            figure_id = max(ModelObject.id_seq) + 1

        ModelObject.id_seq.add(figure_id)
        self.id = self.get_name(figure_id)

    @abstractmethod
    def accept(self, visitor : 'Visitor'):
        pass

    @abstractmethod
    def shoot(self, click: Coord):
        pass

    def __str__(self):
        return self.id

    @abstractmethod
    def get_name(self, num_id):
        pass

    @abstractmethod
    def is_selected(self) -> bool:
        pass