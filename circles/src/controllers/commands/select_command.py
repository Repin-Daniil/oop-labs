from typing import List

from src.controllers.command import Command
from src.domain.visitors.select_visitor import SelectVisitor
from src.model.model_object import ModelObject


class SelectCommand(Command):
    def __init__(self):
        self.target = []
        self.rollback = False


    def execute(self, objects: List[ModelObject]):
        visitor =  SelectVisitor()
        self.target = objects

        for obj in objects:
            obj.accept(visitor)


    def undo(self):
        if not self.rollback:
            self.rollback = True

            visitor =  SelectVisitor()

            for obj in self.target:
                obj.accept(visitor)

    def redo(self):
        if self.rollback:
            self.rollback = False

            visitor = SelectVisitor()

            for obj in self.target:
                obj.accept(visitor)

    def clone(self) -> Command:
        return SelectCommand()


