from typing import List


from src.controllers.command import Command
from src.model.model import Model
from src.model.model_object import ModelObject


class AddCommand(Command):
    def __init__(self, model: Model):
        self.target = []
        self.model = model
        self.rollback = False

    def execute(self,  figures: List[ModelObject]):
        self.target = figures

        for figure in self.target:
            self.model.add_figure(figure)


    def undo(self):
        if not self.rollback:
            self.rollback = True

            for figure in self.target:
                self.model.remove_figure(figure.id)

    def redo(self):
        if self.rollback:
            self.rollback = False

            for figure in self.target:
                self.model.add_figure(figure)

    def clone(self) -> Command:
        return AddCommand(self.model)


