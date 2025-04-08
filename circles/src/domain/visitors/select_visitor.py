from src.domain.visitor import Visitor


class SelectVisitor(Visitor):
    def visit_circle(self, circle: 'Circle'):
        circle.selected = not circle.selected

        if circle.selected:
            print(f"Выделен круг {circle.id}")

        else:
            print(f"Снято выделение с {circle.id}")