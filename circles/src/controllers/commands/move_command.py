from typing import List

from src.controllers.command import Command
from src.domain.visitors.move_visitor import MoveVisitor
from src.domain.visitors.select_visitor import SelectVisitor
from src.model.model_object import ModelObject


class MoveCommand(Command):
    def __init__(self, dx: int, dy: int, canvas_width:int, canvas_height:int):
        self.target = []
        self.rollback = False
        self.dx= dx
        self.dy = dy
        self.canvas_width = canvas_width
        self.canvas_height = canvas_height


    def execute(self, objects: List[ModelObject]):
        visitor =  MoveVisitor(self.dx, self.dy, self.canvas_width, self.canvas_height)
        self.target = objects

        for obj in objects:
            obj.accept(visitor)


    def undo(self):
        if not self.rollback:
            self.rollback = True

            visitor = MoveVisitor(-self.dx, -self.dy, self.canvas_width, self.canvas_height)

            for obj in self.target:
                obj.accept(visitor)

    def redo(self):
        if self.rollback:
            self.rollback = False

            visitor = MoveVisitor(self.dx, self.dy, self.canvas_width, self.canvas_height)

            for obj in self.target:
                obj.accept(visitor)

    def clone(self) -> Command:
        return MoveCommand(self.dx, self.dy, self.canvas_width, self.canvas_height)


