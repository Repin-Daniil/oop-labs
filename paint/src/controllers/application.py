from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QApplication

from src.controllers.command_manager import CommandManager
from src.controllers.input_controller import InputController
from src.domain.standard_factory import StandardFactory
from src.model.model import Model
from src.model.scenarios.select_strategy import SelectStrategy
from src.model.scenarios.strategies.all_select_strategy import AllSelectStrategy
from src.model.scenarios.strategies.back_select_strategy import BackSelectStrategy
from src.model.scenarios.strategies.front_select_strategy import FrontSelectStrategy
from src.view.window import Window

class Application:
    def __init__(self, argv, title: str):
        self.app = QApplication(argv)

        hotkeys = (Qt.Key.Key_Backspace, Qt.Key.Key_Z, Qt.Key.Key_Y,
                   Qt.Key.Key_Left, Qt.Key.Key_Right,
                   Qt.Key.Key_Up, Qt.Key.Key_Down,Qt.Key.Key_Minus, Qt.Key.Key_Equal)

        strategies_dict = {
            "Выбрать верхнего": FrontSelectStrategy(),
            "Выбрать нижнего": BackSelectStrategy(),
            "Выбрать всех": AllSelectStrategy()
        }

        shapes = ["circle", "rectangle", "triangle", "ellipse", "square"]

        self.model = Model(strategies_dict["Выбрать верхнего"])
        self.view = Window(title, self.model, hotkeys, shapes, list(strategies_dict.keys()))
        self.command_manager = CommandManager()


        self.input_controller = InputController(
            model=self.model,
            factory=StandardFactory(),
            command_manager=self.command_manager,
            canvas=self.view.canvas,
            shapes=shapes,
            strategies=list(strategies_dict.values())
        )

        self.view.keyPressed.connect(self.input_controller.handle_key_press)
        self.view.canvas.mouse_clicked.connect(self.input_controller.handle_canvas_click)
        self.view.ui.strategy_combo_box.currentIndexChanged.connect(self.input_controller.change_strategy)
        self.view.ui.shape_combo_box.currentIndexChanged.connect(self.input_controller.change_object_type)
        self.view.ui.color_button.colorChanged.connect(self.input_controller.change_color)

    def run(self):
        self.view.show()
        self.app.exec()
