from PyQt6.QtCore import Qt

from src.controllers.command_manager import CommandManager
from src.controllers.commands.add_command import AddCommand
from src.controllers.commands.delete_command import DeleteCommand
from src.controllers.commands.select_command import SelectCommand
from src.controllers.factory import ObjectFactory
from src.model.model import Model
from src.model.scenarios.geometry import Coord


class InputController:
    """
    Класс, отвечающий за обработку событий (нажатий клавиш, кликов мыши) и
    выполнение соответствующих команд через CommandManager.
    """
    def __init__(self, model: Model, factory: ObjectFactory, command_manager: CommandManager, canvas):
        self.model = model
        self.factory = factory
        self.command_manager = command_manager
        self.canvas = canvas
        # todo регулирование через UI
        self.current_size = 50
        self.current_color = (0, 0, 0)
        self.current_object_type = "circle"

    def handle_key_press(self, key):
        print(f"Pressed key: {key}")
        if key == Qt.Key.Key_Backspace:
            selected = self.model.get_selected()
            if selected:
                # Удаляем выделенные объекты
                delete_command = DeleteCommand( self.model)
                self.command_manager.execute_command(delete_command,selected)
        elif key == Qt.Key.Key_Z:
            print("Undo (Z) pressed")
            self.command_manager.undo()
        elif key == Qt.Key.Key_Y:
            print("Redo (Y) pressed")
            self.command_manager.redo()
        elif key in (Qt.Key.Key_Left, Qt.Key.Key_Right, Qt.Key.Key_Up, Qt.Key.Key_Down):
            print("Arrow key pressed")
            #todo Здесь можно добавить логику перемещения выбранного объекта, в том числе проверить валидность через визитора


        # todo +/- для изменения размера, где тоже нужно будеть проверять валидность
        # todo слайдер для регулировки размера
        #todo цвет нужно выбирать не кнопкой, а просто какую-то штуку сделать, которая будет текущего цвета, при нажатии на нее выделяется
        #todo выбор стратегии выбора
        self.canvas.update()

    def handle_canvas_click(self, pos, modifiers, button):
        if button == Qt.MouseButton.LeftButton:
            click_pos = Coord(int(pos.x()), int(pos.y()))

            if not (modifiers & Qt.KeyboardModifier.ControlModifier):
                # Снимаем выделение с текущих объектов,
                # предполагаем, что SelectCommand без аргументов умеет снимать выделение
                deselection_command = SelectCommand()
                self.command_manager.execute_command(deselection_command, self.model.get_selected())

            selected = self.model.select(click_pos)

            if selected:
                # Выделяем найденные объекты
                selection_command = SelectCommand()
                self.command_manager.execute_command(selection_command, selected)
            else:
                # Если ничего не выделили – создаем новую фигуру.

                #todo нужно поставить ограничения тогда на размер окна, и обработать вдруг выходим за границу окна, отдельный визитор по идее
                figure = self.factory.create_object(
                    self.current_object_type, click_pos, None, self.current_size, self.current_color
                )

                add_command = AddCommand(self.model)
                self.command_manager.execute_command(add_command, [figure])

            self.canvas.update()
