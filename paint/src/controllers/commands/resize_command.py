from typing import List

from src.controllers.command import Command
from src.domain.visitors.move_visitor import MoveVisitor
from src.domain.visitors.resize_visitor import ResizeVisitor
from src.domain.visitors.select_visitor import SelectVisitor
from src.model.model_object import ModelObject


class ResizeCommand(Command):
    def __init__(self, step: int, canvas_width:int, canvas_height:int):
        self.target = []
        self.step = step
        self.rollback = False

        self.canvas_width = canvas_width
        self.canvas_height = canvas_height


    def execute(self, objects: List[ModelObject]):
        visitor =  ResizeVisitor(self.step, self.canvas_width, self.canvas_height)
        self.target = objects

        for obj in objects:
            obj.accept(visitor)


    def undo(self):
        if not self.rollback:
            self.rollback = True
            visitor = ResizeVisitor(-self.step, self.canvas_width, self.canvas_height)

            for obj in self.target:
                obj.accept(visitor)

    def redo(self):
        if self.rollback:
            self.rollback = False

            visitor = ResizeVisitor(self.step, self.canvas_width, self.canvas_height)

            for obj in self.target:
                obj.accept(visitor)

    def clone(self) -> Command:
        return ResizeCommand(self.step, self.canvas_width, self.canvas_height)


