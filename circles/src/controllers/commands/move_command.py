from typing import List

from src.controllers.command import Command
from src.model.actions.visitor import Visitor
from src.model.actions.visitors.move_visitor import MoveVisitor

from src.model.model_object import ModelObject


class MoveCommand(Command):
    def __init__(self, dx: float, dy: float):
        self.target = []
        self.dx = dx
        self.dy = dy

    def execute(self, objects: List[ModelObject]):
        visitor = MoveVisitor(self.dx, self.dy)
        self.target = objects

        for obj in objects:
            obj.accept(visitor)

    def undo(self):
        visitor = MoveVisitor(-self.dx, -self.dy)

        for obj in self.target:
            obj.accept(visitor)


    def clone(self) -> Command:
        return MoveCommand(self.dx, self.dy)

    def get_exec_visitor(self) -> Visitor:
        return

    def get_undo_visitor(self) -> Visitor:
        return

