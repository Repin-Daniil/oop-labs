from PyQt6.QtCore import Qt, QSize
from PyQt6.QtGui import QAction, QFont
from PyQt6.QtWidgets import (
    QMainWindow, QWidget, QVBoxLayout, QHBoxLayout, QLabel,
    QComboBox, QPushButton, QFrame, QMenuBar, QMenu
)

from src.view.canvas import CanvasWidget


class WindowUI:
    """UI setup class for the main window of the vector editor."""

    def setup(self, main_window: QMainWindow) -> None:
        """Setup the main window UI components."""
        self._setup_actions(main_window)
        self._setup_central_widget(main_window)
        self._setup_menu_bar(main_window)
        self._set_texts()


    def attach_canvas(self, canvas: CanvasWidget) -> None:
        self.canvas = canvas
        self.main_layout.addWidget(self.canvas)

    def _setup_actions(self, main_window: QMainWindow) -> None:
        """Create and setup window actions."""
        self.action_import = QAction("Import", main_window)
        self.action_export = QAction("Export", main_window)

    def _setup_central_widget(self, main_window: QMainWindow) -> None:
        """Setup the central widget and its layout."""
        self.central_widget = QWidget(main_window)

        # Main vertical layout
        self.main_layout = QVBoxLayout(self.central_widget)

        # Top toolbar horizontal layout
        toolbar_layout = QHBoxLayout()
        toolbar_layout.setSizeConstraint(QHBoxLayout.SizeConstraint.SetNoConstraint)

        # Title label
        self.title_label = self._create_title_label()
        toolbar_layout.addWidget(self.title_label, 0, Qt.AlignmentFlag.AlignHCenter | Qt.AlignmentFlag.AlignVCenter)

        # Shape selection combo box
        self.shape_combo_box = self._create_combo_box(["Circle"], default_index=0)
        toolbar_layout.addWidget(self.shape_combo_box, 0, Qt.AlignmentFlag.AlignRight)

        # Color selection button
        self.color_button = QPushButton("Choose Color")
        self.color_button.setMinimumSize(QSize(100, 0))
        toolbar_layout.addWidget(self.color_button, 0, Qt.AlignmentFlag.AlignHCenter)

        # Strategy selection combo box
        self.strategy_combo_box = self._create_combo_box(["Strategy 1", "Strategy 2"], default_index=0)
        toolbar_layout.addWidget(self.strategy_combo_box, 0, Qt.AlignmentFlag.AlignLeft)

        self.main_layout.addLayout(toolbar_layout)

        # Separator line
        separator_line = QFrame()
        separator_line.setFrameShape(QFrame.Shape.HLine)
        separator_line.setFrameShadow(QFrame.Shadow.Sunken)
        self.main_layout.addWidget(separator_line)

        main_window.setCentralWidget(self.central_widget)

    def _setup_menu_bar(self, main_window: QMainWindow) -> None:
        """Setup the menu bar."""
        self.menu_bar = QMenuBar(main_window)
        self.menu_bar.setGeometry(0, 0, 800, 38)

        file_menu = QMenu("File", self.menu_bar)
        file_menu.addSeparator()
        file_menu.addAction(self.action_import)
        file_menu.addAction(self.action_export)

        self.menu_bar.addAction(file_menu.menuAction())
        main_window.setMenuBar(self.menu_bar)

    def _create_title_label(self) -> QLabel:
        """Create and configure the title label."""
        label = QLabel()
        label.setMinimumSize(QSize(0, 50))
        label.setMaximumSize(QSize(16777215, 50))

        font = QFont()
        font.setFamilies(["Times New Roman"])
        font.setPointSize(41)
        font.setBold(True)
        font.setItalic(True)
        label.setFont(font)

        return label

    def _create_combo_box(self, items: list[str], default_index: int = 0) -> QComboBox:
        """Create and configure a combo box with given items."""
        combo_box = QComboBox()
        for item in items:
            combo_box.addItem(item)
        combo_box.setCurrentIndex(default_index)
        return combo_box

    def _set_texts(self) -> None:
        """Set all static texts in the UI."""
        self.title_label.setText("Paint")
        self.color_button.setText("Choose Color")