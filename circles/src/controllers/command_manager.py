from src.controllers.command import Command


class CommandManager:
    def __init__(self):
        self.undo_stack = []  # выполненные команды для undo
        self.redo_stack = []  # отменённые команды для redo

    # todo как оповещать канвас об изменениях, наблюдатель?

    def execute_command(self, command:Command, target):
        command.execute(target)
        self.undo_stack.append(command)
        self.redo_stack.clear()

    def undo(self):
        if self.undo_stack:
            command = self.undo_stack.pop()
            command.undo()
            self.redo_stack.append(command)

    def redo(self):
        if self.redo_stack:
            command = self.redo_stack.pop()
            command.redo()
            self.undo_stack.append(command)
