from src.domain.visitor import Visitor


class SelectVisitor(Visitor):
    def visit_circle(self, circle: 'Circle'):
        circle.selected = not circle.selected