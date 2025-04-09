from PyQt6.QtWidgets import QPushButton, QColorDialog
from PyQt6.QtGui import QColor
from PyQt6.QtCore import pyqtSignal

class ColorButton(QPushButton):
    colorChanged = pyqtSignal(QColor)

    def __init__(self, initial_color: QColor = QColor(0, 0, 0), parent=None):
        super().__init__(parent)
        self._color = initial_color
        self.updateStyleSheet()
        self.clicked.connect(self.chooseColor)

    def chooseColor(self):
        color = QColorDialog.getColor(self._color, self, "Выберите цвет")
        if color.isValid() and color != self._color:
            self._color = color
            self.updateStyleSheet()

            self.colorChanged.emit(color)

    def updateStyleSheet(self):
        self.setStyleSheet(f"background-color: {self._color.name()}; border: 1px solid #000;")

    def color(self) -> QColor:
        return self._color
