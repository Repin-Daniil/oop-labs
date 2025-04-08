from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QApplication

from src.controllers.command_manager import CommandManager
from src.controllers.input_controller import InputController
from src.domain.standard_factory import StandardFactory
from src.model.model import Model
from src.view.window import Window




class Application:
    def __init__(self, argv, title: str):
        self.model = Model()
        self.app = QApplication(argv)

        hotkeys = (Qt.Key.Key_Backspace, Qt.Key.Key_Z, Qt.Key.Key_Y,
                   Qt.Key.Key_Left, Qt.Key.Key_Right,
                   Qt.Key.Key_Up, Qt.Key.Key_Down)

        self.view = Window(title, self.model, hotkeys)



        self.command_manager = CommandManager()
        self.input_controller = InputController(
            model=self.model,
            factory=StandardFactory(),
            command_manager=self.command_manager,
            canvas=self.view.canvas,
        )


        self.view.keyPressed.connect(self.input_controller.handle_key_press)
        self.view.canvas.mouse_clicked.connect(self.input_controller.handle_canvas_click)

    def run(self):
        self.view.show()
        self.app.exec()
