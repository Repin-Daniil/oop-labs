from PyQt6.QtGui import QColor, QPen, QBrush, QPolygonF
from PyQt6.QtCore import Qt, QRectF, QPointF

from src.domain.objects.circle import Circle
from src.domain.objects.ellipse import Ellipse
from src.domain.objects.square import Square
from src.domain.objects.triangle import Triangle
from src.domain.visitor import Visitor
from src.model.scenarios.geometry import Rectangle


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

    def visit_rectangle(self, rectangle: Rectangle):
        top_left = rectangle.top_left
        width = rectangle.width
        height = rectangle.height

        self.set_color(rectangle.get_color())
        self.painter.drawRect(top_left.x, top_left.y, width, height)

        if rectangle.selected:
            rect = QRectF(top_left.x, top_left.y, width, height)
            self.draw_selection_rect(rect)

    def visit_triangle(self, triangle: Triangle):
        p1, p2, p3 = triangle.get_points()
        self.set_color(triangle.get_color())

        # Создаем полигон из трех вершин для отрисовки треугольника.
        polygon = QPolygonF([
            QPointF(p1.x, p1.y),
            QPointF(p2.x, p2.y),
            QPointF(p3.x, p3.y)
        ])
        self.painter.drawPolygon(polygon)

        if triangle.selected:
            # Получаем ограничивающий прямоугольник для треугольника.
            left, right, top, bottom = triangle.get_bounding_box()
            rect = QRectF(left, top, right - left, bottom - top)
            self.draw_selection_rect(rect)

    def visit_square(self, square: Square):
        top_left = square.top_left
        size = square.side_length

        self.set_color(square.get_color())
        self.painter.drawRect(top_left.x, top_left.y, size, size)

        if square.selected:
            rect = QRectF(top_left.x, top_left.y, size, size)
            self.draw_selection_rect(rect)

    def visit_ellipse(self, ellipse: Ellipse):
        center = ellipse.center
        rx = ellipse.radius_x
        ry = ellipse.radius_y

        self.set_color(ellipse.get_color())
        self.painter.drawEllipse(center.x - rx, center.y - ry, rx * 2, ry * 2)

        if ellipse.selected:
            rect = QRectF(center.x - rx, center.y - ry, rx * 2, ry * 2)
            self.draw_selection_rect(rect)