from PyQt6.QtCore import Qt, pyqtSignal
from PyQt6.QtWidgets import QMainWindow

from src.view.canvas import CanvasWidget
from src.view.ui import WindowUI


class Window(QMainWindow):
    keyPressed = pyqtSignal(Qt.Key)

    def __init__(self, title: str, model, hotkeys, shapes:list[str], strategies:list[str]):
        super(Window, self).__init__()
        self.hotkeys = hotkeys

        self.setWindowTitle(title)
        self.resize(800, 600)
        self.setMinimumSize(600, 400)

        self.ui = WindowUI()
        self.ui.setup(self, shapes, strategies)

        self.canvas = CanvasWidget(model, self)

        self.ui.attach_canvas(self.canvas)



    def keyPressEvent(self, event):
        key = Qt.Key(event.key())

        if key in self.hotkeys:
            self.keyPressed.emit(key)

        else:
            super().keyPressEvent(event)