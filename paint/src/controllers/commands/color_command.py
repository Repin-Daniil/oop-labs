from typing import List
from src.controllers.command import Command
from src.domain.visitors.color_visitor import ColorVisitor
from src.model.model_object import ModelObject


class ChangeColorCommand(Command):
    def __init__(self, new_color: tuple[int, int, int]):
        self.target: List[ModelObject] = []
        self.rollback = False
        self.new_color = new_color
        self.old_colors: List[tuple[int, int, int]] = []

    def execute(self, objects: List[ModelObject]):
        self.target = objects
        self.old_colors.clear()

        for obj in self.target:
            visitor = ColorVisitor(self.new_color)
            obj.accept(visitor)
            self.old_colors.append(visitor.old_color)

    def undo(self):
        if not self.rollback:
            self.rollback = True
            for obj, old_color in zip(self.target, self.old_colors):
                visitor = ColorVisitor(old_color)
                obj.accept(visitor)

    def redo(self):
        if self.rollback:
            self.rollback = False
            for obj in self.target:
                visitor = ColorVisitor(self.new_color)
                obj.accept(visitor)

    def clone(self) -> Command:
        return ChangeColorCommand(self.new_color)
