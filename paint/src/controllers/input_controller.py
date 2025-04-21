from PyQt6.QtCore import Qt

from src.controllers.command_manager import CommandManager
from src.controllers.commands.add_command import AddCommand
from src.controllers.commands.color_command import ChangeColorCommand
from src.controllers.commands.delete_command import DeleteCommand
from src.controllers.commands.move_command import MoveCommand
from src.controllers.commands.resize_command import ResizeCommand
from src.controllers.commands.select_command import SelectCommand
from src.controllers.factory import ObjectFactory
from src.model.model import Model
from src.model.scenarios.geometry import Coord, normalize_figure
from src.model.scenarios.select_strategy import SelectStrategy


class InputController:
    """
    Класс, отвечающий за обработку событий (нажатий клавиш, кликов мыши) и
    выполнение соответствующих команд через CommandManager.
    """

    def __init__(self, model: Model, factory: ObjectFactory, command_manager: CommandManager, canvas, shapes,
                 strategies):
        self.model = model
        self.factory = factory
        self.shapes = shapes
        self.command_manager = command_manager
        self.canvas = canvas

        self.current_size = 50
        self.current_color = (0, 0, 0)
        self.current_object_type = "circle"
        self.strategies = strategies

    def handle_key_press(self, key):
        if key == Qt.Key.Key_Backspace:
            selected = self.model.get_selected()
            if selected:
                # Удаляем выделенные объекты
                delete_command = DeleteCommand(self.model)
                self.command_manager.execute_command(delete_command, selected)
        elif key == Qt.Key.Key_Z:
            self.command_manager.undo()
        elif key == Qt.Key.Key_Y:
            self.command_manager.redo()
        elif key in (Qt.Key.Key_Minus, Qt.Key.Key_Equal):
            delta = -10 if key == Qt.Key.Key_Minus else 10
            resize_command = ResizeCommand(delta, self.canvas.width(), self.canvas.height())
            self.command_manager.execute_command(resize_command, self.model.get_selected())

        elif key in (Qt.Key.Key_Left, Qt.Key.Key_Right, Qt.Key.Key_Up, Qt.Key.Key_Down):
            if key == Qt.Key.Key_Left:
                move_command = MoveCommand(-5, 0, self.canvas.width(), self.canvas.height())
                self.command_manager.execute_command(move_command, self.model.get_selected())

            elif key == Qt.Key.Key_Right:
                move_command = MoveCommand(5, 0, self.canvas.width(), self.canvas.height())
                self.command_manager.execute_command(move_command, self.model.get_selected())

            elif key == Qt.Key.Key_Down:
                move_command = MoveCommand(0, 5, self.canvas.width(), self.canvas.height())
                self.command_manager.execute_command(move_command, self.model.get_selected())

            elif key == Qt.Key.Key_Up:
                move_command = MoveCommand(0, -5, self.canvas.width(), self.canvas.height())
                self.command_manager.execute_command(move_command, self.model.get_selected())

        self.canvas.update()

    def handle_canvas_click(self, pos, modifiers, button):
        if button == Qt.MouseButton.LeftButton:
            click_pos = Coord(int(pos.x()), int(pos.y()))

            selected = self.model.select(click_pos)

            if not (modifiers & Qt.KeyboardModifier.ControlModifier):


                if selected != self.model.get_selected():
                    deselection_command = SelectCommand()
                    self.command_manager.execute_command(deselection_command, self.model.get_selected())



            if selected:
                selection_command = SelectCommand()
                self.command_manager.execute_command(selection_command, selected)
            else:
                if not (modifiers & Qt.KeyboardModifier.ControlModifier):
                    figure = self.factory.create_object(
                        self.current_object_type, click_pos, None, self.canvas.width(), self.canvas.height(),
                        self.current_size, self.current_color
                    )

                    add_command = AddCommand(self.model)
                    self.command_manager.execute_command(add_command, [figure])

            self.canvas.update()

    def change_strategy(self, index: int):
        self.model.set_select_policy(self.strategies[index])

    def change_color(self, color):
        self.current_color = (color.red(), color.green(), color.blue())
        color_command = ChangeColorCommand((color.red(), color.green(), color.blue()))
        self.command_manager.execute_command(color_command, self.model.get_selected())

    def change_object_type(self, index: int):
        self.current_object_type = self.shapes[index]
