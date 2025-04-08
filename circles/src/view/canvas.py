from PyQt6.QtWidgets import QWidget
from PyQt6.QtGui import QPainter
from src.view.draw_visitor import DrawingVisitor
from src.model.model import Model
from PyQt6.QtCore import pyqtSignal, QPointF, Qt


class CanvasWidget(QWidget):
    mouse_clicked = pyqtSignal(QPointF, Qt.KeyboardModifier, Qt.MouseButton)

    def __init__(self, model: Model):
        super().__init__()
        self.model = model

    def paintEvent(self, event):
        painter = QPainter(self)
        visitor = DrawingVisitor(painter)

        for obj in self.model.objects:
            obj.accept(visitor)

    def mousePressEvent(self, event):
        self.mouse_clicked.emit(event.position(), event.modifiers(), event.button())