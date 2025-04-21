from src.domain.objects.ellipse import Ellipse
from src.domain.objects.rectangle import Rectangle
from src.domain.objects.square import Square
from src.domain.objects.triangle import Triangle
from src.domain.visitor import Visitor
from src.model.scenarios.geometry import normalize_figure, Coord


class ResizeVisitor(Visitor):
    def __init__(self, step: int, canvas_width: int, canvas_height: int):
        self.step = step
        self.canvas_width = canvas_width
        self.canvas_height = canvas_height

    def visit_circle(self, circle):
        circle.radius  = max(10, min(200, circle.radius + self.step))
        dx, dy = normalize_figure(self.canvas_width, self.canvas_height, circle.get_bounding_box())
        circle.center += Coord(dx, dy)

    def visit_rectangle(self, rectangle: Rectangle):
        rectangle.width = max(10, min(200, rectangle.width + self.step))
        rectangle.height = max(10, min(200, rectangle.height + self.step))
        dx, dy = normalize_figure(self.canvas_width, self.canvas_height, rectangle.get_bounding_box())
        rectangle.top_left += Coord(dx, dy)
        return rectangle

    def visit_triangle(self, triangle: Triangle) -> Triangle:
        center = triangle.get_center()

        def move_point_outward(pt: Coord) -> Coord:
            dx = pt.x - center.x
            dy = pt.y - center.y
            length = (dx ** 2 + dy ** 2) ** 0.5
            if length == 0:
                return pt  # точка совпадает с центром — не двигаем
            scale = min(self.step, 200 - length) if length < 200 else 0  # не выходим за пределы
            return Coord(
                int(pt.x + dx / length * scale),
                int(pt.y + dy / length * scale)
            )

        # Применяем смещение ко всем точкам
        triangle.p1 = move_point_outward(triangle.p1)
        triangle.p2 = move_point_outward(triangle.p2)
        triangle.p3 = move_point_outward(triangle.p3)

        # Нормализация положения (центрирование)
        bbox = triangle.get_bounding_box()
        dx, dy = normalize_figure(self.canvas_width, self.canvas_height, bbox)
        offset = Coord(dx, dy)
        triangle.p1 += offset
        triangle.p2 += offset
        triangle.p3 += offset

        return triangle
    
    def visit_square(self, square: Square):
        square.side_length = max(10, min(200, square.side_length + self.step))
        dx, dy = normalize_figure(self.canvas_width, self.canvas_height, square.get_bounding_box())
        square.top_left += Coord(dx, dy)
        return square

    def visit_ellipse(self, ellipse: Ellipse):
        ellipse.radius_x  = max(10, min(200, ellipse.radius_x + self.step))
        ellipse.radius_y = max(10, min(200, ellipse.radius_y + self.step))

        dx, dy = normalize_figure(self.canvas_width, self.canvas_height, ellipse.get_bounding_box())
        ellipse.center += Coord(dx, dy)

