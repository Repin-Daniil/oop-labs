import sys

from src.controllers.application import Application
from src.domain.standard_factory import StandardFactory

if __name__ == '__main__':
    app = Application(sys.argv, "Наивный редактор")
    app.run()