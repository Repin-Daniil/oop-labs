import math
from math import hypot
from typing import Union


class Coord:
    def __init__(self, x: int, y: int):
        self._x = x
        self._y = y

    @property
    def x(self) -> int:
        return self._x

    @property
    def y(self) -> int:
        return self._y

    def __add__(self, other: 'Coord') -> 'Coord':
        """Сложение координат (оператор +)"""
        return Coord(self.x + other.x, self.y + other.y)

    def __sub__(self, other: 'Coord') -> 'Coord':
        """Вычитание координат (оператор -)"""
        return Coord(self.x - other.x, self.y - other.y)

    def __mul__(self, scalar: float) -> 'Coord':
        """Умножение на скаляр (оператор *)"""
        return Coord(int(self.x * scalar), int(self.y * scalar))

    def __eq__(self, other: object) -> bool:
        """Проверка на равенство (оператор ==)"""
        if not isinstance(other, Coord):
            return False
        return self.x == other.x and self.y == other.y

    def __repr__(self) -> str:
        """Строковое представление для отладки"""
        return f"Coord({self.x}, {self.y})"


class Line:
    def __init__(self, start: Coord, end: Coord):
        self.start = start
        self.end = end

    def length(self) -> float:
        """Длина линии"""
        return GetDistance(self.start, self.end)

    def get_midpoint(self) -> Coord:
        """Середина линии"""
        return Coord(
            (self.start.x + self.end.x) // 2,
            (self.start.y + self.end.y) // 2
        )


class Rectangle:
    def __init__(self, top_left: Coord, width: int, height: int):
        self.top_left = top_left
        self.width = width
        self.height = height

    def area(self) -> int:
        return self.width * self.height

    def contains_point(self, point: Coord) -> bool:
        return (self.top_left.x <= point.x <= self.top_left.x + self.width and
                self.top_left.y <= point.y <= self.top_left.y + self.height)

def GetDistance(lhs: Coord, rhs: Coord) -> float:
    return hypot(abs(lhs.y - rhs.y), abs(lhs.x - rhs.x))


def is_point_on_line(point: Coord, line: Line, tolerance: float = 1.0) -> bool:
    total_length = line.length()
    d1 = GetDistance(point, line.start)
    d2 = GetDistance(point, line.end)
    return abs(d1 + d2 - total_length) < tolerance


def get_angle_between_lines(line1: Line, line2: Line) -> float:
    vec1 = Coord(line1.end.x - line1.start.x, line1.end.y - line1.start.y)
    vec2 = Coord(line2.end.x - line2.start.x, line2.end.y - line2.start.y)

    # Скалярное произведение
    dot = vec1.x * vec2.x + vec1.y * vec2.y

    # Модули векторов
    mod1 = hypot(vec1.x, vec1.y)
    mod2 = hypot(vec2.x, vec2.y)

    cos_angle = dot / (mod1 * mod2)
    return math.acos(cos_angle)


def get_bounding_box(points: list[Coord]) -> tuple[Coord, Coord]:
    if not points:
        raise ValueError("Empty points list")

    min_x = min(p.x for p in points)
    min_y = min(p.y for p in points)
    max_x = max(p.x for p in points)
    max_y = max(p.y for p in points)

    return Coord(min_x, min_y), Coord(max_x, max_y)


def are_lines_parallel(line1: Line, line2: Line, angle_tolerance: float = 0.01) -> bool:
    angle = get_angle_between_lines(line1, line2)
    return angle < angle_tolerance or abs(angle - math.pi) < angle_tolerance