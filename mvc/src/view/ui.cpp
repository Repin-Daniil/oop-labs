#include "ui.hpp"

namespace mvc::view {

void NumbersUi::setup(QMainWindow* MainWindow) {
  if (MainWindow->objectName().isEmpty()) MainWindow->setObjectName("MainWindow");
  MainWindow->resize(900, 500);
  centralwidget = new QWidget(MainWindow);
  centralwidget->setObjectName("centralwidget");
  verticalLayout = new QVBoxLayout(centralwidget);
  verticalLayout->setObjectName("verticalLayout");
  verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

  verticalLayout->addItem(verticalSpacer_2);

  main_title = new QLabel(centralwidget);
  main_title->setObjectName("main_title");
  main_title->setMinimumSize(QSize(0, 100));
  QFont font;
  font.setFamilies({QString::fromUtf8("Times New Roman")});
  font.setPointSize(64);
  font.setBold(true);
  main_title->setFont(font);
  main_title->setText("A   <=   B   <=   C");

  verticalLayout->addWidget(main_title, 0, Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignBottom);

  main_horizontal_layout = new QHBoxLayout();
  main_horizontal_layout->setObjectName("main_horizontal_layout");
  a_vertical_layout = new QVBoxLayout();
  a_vertical_layout->setObjectName("a_vertical_layout");
  a_change_label = new QLabel(centralwidget);
  a_change_label->setObjectName("a_change_label");
  a_change_label->setText("Изменение значения A");
  QFont h_three_font;
  h_three_font.setFamilies({QString::fromUtf8("Times New Roman")});
  h_three_font.setPointSize(18);
  h_three_font.setBold(true);

  a_change_label->setFont(h_three_font);

  a_vertical_layout->addWidget(a_change_label, 0, Qt::AlignmentFlag::AlignHCenter);

  a_line_input = new QLineEdit(centralwidget);
  a_line_input->setObjectName("a_line_input");
  a_line_input->setPlaceholderText("Введите значение A");

  a_vertical_layout->addWidget(a_line_input);

  a_spin_box = new QSpinBox(centralwidget);
  a_spin_box->setObjectName("a_spin_box");
  a_spin_box->setMaximum(100);

  a_vertical_layout->addWidget(a_spin_box);

  a_slider = new QSlider(centralwidget);
  a_slider->setObjectName("a_slider");
  a_slider->setOrientation(Qt::Orientation::Horizontal);

  a_vertical_layout->addWidget(a_slider);

  a_progress_bar = new QProgressBar(centralwidget);
  a_progress_bar->setObjectName("a_progress_bar");
  a_progress_bar->setValue(24);

  a_vertical_layout->addWidget(a_progress_bar);

  verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

  a_vertical_layout->addItem(verticalSpacer_7);

  verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

  a_vertical_layout->addItem(verticalSpacer_6);

  verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

  a_vertical_layout->addItem(verticalSpacer_3);

  a_settings_title = new QLabel(centralwidget);
  a_settings_title->setObjectName("a_settings_title");
  a_settings_title->setText("Настройки A");

  a_settings_title->setFont(h_three_font);

  a_vertical_layout->addWidget(a_settings_title, 0, Qt::AlignmentFlag::AlignHCenter);

  a_runner_layout = new QHBoxLayout();
  a_runner_layout->setObjectName("a_runner_layout");
  a_runner_label = new QLabel(centralwidget);
  a_runner_label->setObjectName("a_runner_label");
  QFont normal_font;
  normal_font.setFamilies({QString::fromUtf8("Times New Roman")});
  normal_font.setPointSize(14);
  a_runner_label->setFont(normal_font);
  a_runner_label->setText("Карусель");

  a_runner_layout->addWidget(a_runner_label);

  // a_runner_input = new QLineEdit(centralwidget);
  // a_runner_input->setObjectName("a_runner_input");
  // a_runner_input->setPlaceholderText("Время задержки");

  // a_runner_layout->addWidget(a_runner_input);

  a_runner_button = new QPushButton(centralwidget);
  a_runner_button->setObjectName("a_runner_button");
  a_runner_button->setText("Запуск");

  a_runner_layout->addWidget(a_runner_button);

  a_vertical_layout->addLayout(a_runner_layout);

  a_policy_layout = new QHBoxLayout();
  a_policy_layout->setObjectName("a_policy_layout");
  a_policy_label = new QLabel(centralwidget);
  a_policy_label->setObjectName("a_policy_label");
  a_policy_label->setFont(normal_font);
  a_policy_label->setText("Выбор политики");

  a_policy_layout->addWidget(a_policy_label, 0, Qt::AlignmentFlag::AlignLeft);

  a_policy_combo_box = new QComboBox(centralwidget);
  a_policy_combo_box->setObjectName("a_policy_combo_box");
  a_policy_combo_box->setMinimumSize(QSize(200, 0));
  a_policy_combo_box->setMaximumSize(QSize(123, 32));

  a_policy_layout->addWidget(a_policy_combo_box, 0, Qt::AlignmentFlag::AlignRight);

  a_vertical_layout->addLayout(a_policy_layout);

  main_horizontal_layout->addLayout(a_vertical_layout);

  b_vertical_layout = new QVBoxLayout();
  b_vertical_layout->setObjectName("b_vertical_layout");
  b_changel_label = new QLabel(centralwidget);
  b_changel_label->setObjectName("b_changel_label");
  b_changel_label->setFont(h_three_font);

  b_vertical_layout->addWidget(b_changel_label, 0, Qt::AlignmentFlag::AlignHCenter);

  b_line_input = new QLineEdit(centralwidget);
  b_line_input->setObjectName("b_line_input");
  b_line_input->setPlaceholderText("Введите значение B");

  b_vertical_layout->addWidget(b_line_input);

  b_spin_box = new QSpinBox(centralwidget);
  b_spin_box->setObjectName("b_spin_box");
  b_spin_box->setMaximum(100);

  b_vertical_layout->addWidget(b_spin_box);

  b_slider = new QSlider(centralwidget);
  b_slider->setObjectName("b_slider");
  b_slider->setOrientation(Qt::Orientation::Horizontal);

  b_vertical_layout->addWidget(b_slider);

  b_progress_bar = new QProgressBar(centralwidget);
  b_progress_bar->setObjectName("b_progress_bar");
  b_progress_bar->setValue(24);

  b_vertical_layout->addWidget(b_progress_bar);

  verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

  b_vertical_layout->addItem(verticalSpacer_4);

  verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

  b_vertical_layout->addItem(verticalSpacer_9);

  verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

  b_vertical_layout->addItem(verticalSpacer_8);

  b_settings_title = new QLabel(centralwidget);
  b_settings_title->setObjectName("b_settings_title");
  b_settings_title->setFont(h_three_font);

  b_vertical_layout->addWidget(b_settings_title, 0, Qt::AlignmentFlag::AlignHCenter);

  b_runner_layout = new QHBoxLayout();
  b_runner_layout->setObjectName("b_runner_layout");
  b_runner_label = new QLabel(centralwidget);
  b_runner_label->setObjectName("b_runner_label");
  b_runner_label->setFont(normal_font);

  b_runner_layout->addWidget(b_runner_label);

  // b_runner_input = new QLineEdit(centralwidget);
  // b_runner_input->setObjectName("b_runner_input");
  // b_runner_input->setPlaceholderText("Время задержки");

  // b_runner_layout->addWidget(b_runner_input);

  b_runner_button = new QPushButton(centralwidget);
  b_runner_button->setObjectName("b_runner_button");

  b_runner_layout->addWidget(b_runner_button);

  b_vertical_layout->addLayout(b_runner_layout);

  horizontalLayout_6 = new QHBoxLayout();
  horizontalLayout_6->setObjectName("horizontalLayout_6");
  b_policy_label = new QLabel(centralwidget);
  b_policy_label->setObjectName("b_policy_label");
  b_policy_label->setFont(normal_font);

  horizontalLayout_6->addWidget(b_policy_label, 0, Qt::AlignmentFlag::AlignLeft);

  b_policy_combo_box = new QComboBox(centralwidget);
  b_policy_combo_box->setObjectName("b_policy_combo_box");
  b_policy_combo_box->setMinimumSize(QSize(200, 0));

  horizontalLayout_6->addWidget(b_policy_combo_box, 0, Qt::AlignmentFlag::AlignRight);

  b_vertical_layout->addLayout(horizontalLayout_6);

  main_horizontal_layout->addLayout(b_vertical_layout);

  c_vertical_layout = new QVBoxLayout();
  c_vertical_layout->setObjectName("c_vertical_layout");
  c_change_label = new QLabel(centralwidget);
  c_change_label->setObjectName("c_change_label");
  c_change_label->setFont(h_three_font);

  c_vertical_layout->addWidget(c_change_label, 0, Qt::AlignmentFlag::AlignHCenter);

  c_line_input = new QLineEdit(centralwidget);
  c_line_input->setObjectName("c_line_input");
  c_line_input->setPlaceholderText("Введите значение C");

  c_vertical_layout->addWidget(c_line_input);

  c_spin_box = new QSpinBox(centralwidget);
  c_spin_box->setObjectName("c_spin_box");
  c_spin_box->setMaximum(100);

  c_vertical_layout->addWidget(c_spin_box);

  c_slider = new QSlider(centralwidget);
  c_slider->setObjectName("c_slider");
  c_slider->setOrientation(Qt::Orientation::Horizontal);

  c_vertical_layout->addWidget(c_slider);

  c_progress_bar = new QProgressBar(centralwidget);
  c_progress_bar->setObjectName("c_progress_bar");
  c_progress_bar->setValue(24);

  c_vertical_layout->addWidget(c_progress_bar);

  verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

  c_vertical_layout->addItem(verticalSpacer_5);

  verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

  c_vertical_layout->addItem(verticalSpacer_10);

  verticalSpacer_12 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

  c_vertical_layout->addItem(verticalSpacer_12);

  verticalSpacer_11 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

  c_vertical_layout->addItem(verticalSpacer_11);

  c_settings_title = new QLabel(centralwidget);
  c_settings_title->setObjectName("c_settings_title");
  c_settings_title->setFont(h_three_font);

  c_vertical_layout->addWidget(c_settings_title, 0, Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignVCenter);

  c_runner_layout = new QHBoxLayout();
  c_runner_layout->setObjectName("c_runner_layout");
  c_runner_label = new QLabel(centralwidget);
  c_runner_label->setObjectName("c_runner_label");
  c_runner_label->setFont(normal_font);

  c_runner_layout->addWidget(c_runner_label);

  // c_runner_input = new QLineEdit(centralwidget);
  // c_runner_input->setObjectName("c_runner_input");
  // c_runner_input->setPlaceholderText("Время задержки");

  // c_runner_layout->addWidget(c_runner_input);

  c_runner_button = new QPushButton(centralwidget);
  c_runner_button->setObjectName("c_runner_button");

  c_runner_layout->addWidget(c_runner_button);

  c_vertical_layout->addLayout(c_runner_layout);

  horizontalLayout_7 = new QHBoxLayout();
  horizontalLayout_7->setObjectName("horizontalLayout_7");
  c_policy_label = new QLabel(centralwidget);
  c_policy_label->setObjectName("c_policy_label");
  c_policy_label->setFont(normal_font);

  horizontalLayout_7->addWidget(c_policy_label, 0, Qt::AlignmentFlag::AlignLeft);

  c_policy_combo_box = new QComboBox(centralwidget);
  c_policy_combo_box->setObjectName("c_policy_combo_box");
  c_policy_combo_box->setMinimumSize(QSize(200, 0));

  horizontalLayout_7->addWidget(c_policy_combo_box, 0, Qt::AlignmentFlag::AlignRight);

  c_vertical_layout->addLayout(horizontalLayout_7);

  main_horizontal_layout->addLayout(c_vertical_layout);

  verticalLayout->addLayout(main_horizontal_layout);

  verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

  verticalLayout->addItem(verticalSpacer);

  MainWindow->setCentralWidget(centralwidget);

  MainWindow->setWindowTitle("ЛР №3: MVC");
  b_changel_label->setText("Изменение значения B");
  b_settings_title->setText("Настройки B");
  b_runner_label->setText("Карусель");
  b_runner_button->setText("Запуск");
  b_policy_label->setText("Выбор политики");
  c_change_label->setText("Изменение значения C");
  c_settings_title->setText("Настройки C");
  c_runner_label->setText("Карусель");
  c_runner_button->setText("Запуск");
  c_policy_label->setText("Выбор политики");

  QMetaObject::connectSlotsByName(MainWindow);
}

}  // namespace mvc::gui
