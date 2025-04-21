from abc import ABC, abstractmethod

class Observer(ABC):
    @abstractmethod
    def on_changed(self, subject: 'Subject'):
        pass