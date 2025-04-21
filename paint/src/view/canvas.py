from PyQt6.QtWidgets import QWidget
from PyQt6.QtGui import QPainter
from src.view.draw_visitor import DrawingVisitor
from src.model.model import Model
from PyQt6.QtCore import pyqtSignal, QPointF, Qt, QSize


class CanvasWidget(QWidget):
    mouse_clicked = pyqtSignal(QPointF, Qt.KeyboardModifier, Qt.MouseButton)

    def __init__(self, model: Model, window):
        super().__init__()
        self.model = model
        self.window = window

    def paintEvent(self, event):
        painter = QPainter(self)
        visitor = DrawingVisitor(painter)

        min_width = 600
        min_height = 400

        for obj in self.model.objects:
            obj.accept(visitor)
            left, right, top, bottom = obj.get_bounding_box()
            min_width = int(max(right + (self.window.width() - self.width()), min_width))
            min_height = int(max(bottom + (self.window.height() - self.height()), min_height))


        self.window.setMinimumSize(min_width,min_height)


    def mousePressEvent(self, event):
        self.mouse_clicked.emit(event.position(), event.modifiers(), event.button())


