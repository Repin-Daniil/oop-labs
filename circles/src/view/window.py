from PyQt6.QtCore import Qt, pyqtSignal
from PyQt6.QtWidgets import QMainWindow

from src.view.canvas import CanvasWidget
from src.view.ui import WindowUI


class Window(QMainWindow):
    keyPressed = pyqtSignal(Qt.Key)

    def __init__(self, title: str, model, hotkeys):
        super(Window, self).__init__()
        self.hotkeys = hotkeys

        self.setWindowTitle(title)
        self.resize(800, 600)
        self.setMinimumSize(600, 400)

        self.ui = WindowUI()
        self.ui.setup(self)

        self.canvas = CanvasWidget(model)
        self.ui.attach_canvas(self.canvas)
        # todo Добавление нужных полей в комбо боксы



    def keyPressEvent(self, event):
        key = Qt.Key(event.key())

        if key in self.hotkeys:
            self.keyPressed.emit(key)

        else:
            super().keyPressEvent(event)