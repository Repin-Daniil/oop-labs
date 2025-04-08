from PyQt6.QtGui import QColor, QPen, QBrush
from PyQt6.QtCore import Qt, QRectF

from src.domain.objects.circle import Circle
from src.domain.visitor import Visitor


class DrawingVisitor(Visitor):
    def __init__(self, painter):
        self.painter = painter

    def set_color(self, rgb):
        """Устанавливает цвет пера и кисти по RGB."""

        if rgb is not None:
            color = QColor(*rgb)
        else:
            color = QColor(0, 0, 0)

        self.painter.setPen(QPen(color))
        self.painter.setBrush(QBrush(color))

    def draw_selection_rect(self, bounding_rect: QRectF):
        """Рисует пунктирный прямоугольник вокруг фигуры."""
        selection_pen = QPen(QColor(255, 0, 0))
        selection_pen.setStyle(Qt.PenStyle.DashLine)
        selection_pen.setWidth(1)

        self.painter.setPen(selection_pen)
        self.painter.setBrush(Qt.BrushStyle.NoBrush)
        self.painter.drawRect(bounding_rect)

    def visit_circle(self, circle: Circle):
        center = circle.get_center()
        radius = circle.get_radius()

        self.set_color(circle.get_color())

        self.painter.drawEllipse(center.x - radius,
                                 center.y - radius,
                                 radius * 2,
                                 radius * 2)

        if circle.selected:
            rect = QRectF(center.x - radius,
                          center.y - radius,
                          radius * 2,
                          radius * 2)
            self.draw_selection_rect(rect)
