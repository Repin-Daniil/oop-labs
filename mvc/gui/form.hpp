#pragma once

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <app/runner/runners.hpp>

#include <observer/observer.hpp>

namespace mvc::gui {

class Form : public IListener {
 public:
  explicit Form(int argc, char** argv, model::DeepThought& model, app::Runners& runners);
  void OnChanged() noexcept override;
  void Show();

    private:
    model::DeepThought& model_;
    app::Runners& runners_;
};

}  // namespace mvc::gui

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow : public mvc::gui::Form {};
}  // namespace Ui

QT_END_NAMESPACE

class Ui_MainWindow {
 public:
  QWidget* centralwidget;
  QVBoxLayout* verticalLayout;
  QSpacerItem* verticalSpacer_2;
  QLabel* main_title;
  QHBoxLayout* main_horizontal_layout;
  QVBoxLayout* a_vertical_layout;
  QLabel* a_change_label;
  QLineEdit* a_line_input;
  QSpinBox* a_spin_box;
  QSlider* a_slider;
  QProgressBar* a_progress_bar;
  QSpacerItem* verticalSpacer_7;
  QSpacerItem* verticalSpacer_6;
  QSpacerItem* verticalSpacer_3;
  QLabel* a_settings_title;
  QHBoxLayout* a_runner_layout;
  QLabel* a_runner_label;
  QLineEdit* a_runner_input;
  QPushButton* a_runner_button;
  QHBoxLayout* a_policy_layout;
  QLabel* a_policy_label;
  QComboBox* a_policy_combo_box;
  QVBoxLayout* b_vertical_layout;
  QLabel* b_changel_label;
  QLineEdit* b_line_input;
  QSpinBox* b_spin_box;
  QSlider* b_slider;
  QProgressBar* b_progress_bar;
  QSpacerItem* verticalSpacer_4;
  QSpacerItem* verticalSpacer_9;
  QSpacerItem* verticalSpacer_8;
  QLabel* b_settings_title;
  QHBoxLayout* b_runner_layout;
  QLabel* b_runner_label;
  QLineEdit* b_runner_input;
  QPushButton* b_runner_button;
  QHBoxLayout* horizontalLayout_6;
  QLabel* b_policy_label;
  QComboBox* b_policy_combo_box;
  QVBoxLayout* c_vertical_layout;
  QLabel* c_change_label;
  QLineEdit* c_line_input;
  QSpinBox* c_spin_box;
  QSlider* c_slider;
  QProgressBar* c_progress_bar;
  QSpacerItem* verticalSpacer_5;
  QSpacerItem* verticalSpacer_10;
  QSpacerItem* verticalSpacer_12;
  QSpacerItem* verticalSpacer_11;
  QLabel* c_settings_title;
  QHBoxLayout* c_runner_layout;
  QLabel* c_runner_label;
  QLineEdit* c_runner_input;
  QPushButton* c_runner_button;
  QHBoxLayout* horizontalLayout_7;
  QLabel* c_policy_label;
  QComboBox* c_policy_combo_box;
  QSpacerItem* verticalSpacer;

  void setupUi(QMainWindow* MainWindow) {
    if (MainWindow->objectName().isEmpty()) MainWindow->setObjectName("MainWindow");
    MainWindow->resize(859, 487);
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

    verticalLayout->addWidget(main_title, 0, Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignBottom);

    main_horizontal_layout = new QHBoxLayout();
    main_horizontal_layout->setObjectName("main_horizontal_layout");
    a_vertical_layout = new QVBoxLayout();
    a_vertical_layout->setObjectName("a_vertical_layout");
    a_change_label = new QLabel(centralwidget);
    a_change_label->setObjectName("a_change_label");
    QFont font1;
    font1.setFamilies({QString::fromUtf8("Times New Roman")});
    font1.setPointSize(18);
    font1.setBold(true);
    font1.setItalic(false);
    a_change_label->setFont(font1);

    a_vertical_layout->addWidget(a_change_label, 0, Qt::AlignmentFlag::AlignHCenter);

    a_line_input = new QLineEdit(centralwidget);
    a_line_input->setObjectName("a_line_input");

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
    QFont font2;
    font2.setFamilies({QString::fromUtf8("Times New Roman")});
    font2.setPointSize(18);
    font2.setBold(true);
    a_settings_title->setFont(font2);

    a_vertical_layout->addWidget(a_settings_title, 0, Qt::AlignmentFlag::AlignHCenter);

    a_runner_layout = new QHBoxLayout();
    a_runner_layout->setObjectName("a_runner_layout");
    a_runner_label = new QLabel(centralwidget);
    a_runner_label->setObjectName("a_runner_label");
    QFont font3;
    font3.setFamilies({QString::fromUtf8("Times New Roman")});
    font3.setPointSize(14);
    a_runner_label->setFont(font3);

    a_runner_layout->addWidget(a_runner_label);

    a_runner_input = new QLineEdit(centralwidget);
    a_runner_input->setObjectName("a_runner_input");

    a_runner_layout->addWidget(a_runner_input);

    a_runner_button = new QPushButton(centralwidget);
    a_runner_button->setObjectName("a_runner_button");

    a_runner_layout->addWidget(a_runner_button);

    a_vertical_layout->addLayout(a_runner_layout);

    a_policy_layout = new QHBoxLayout();
    a_policy_layout->setObjectName("a_policy_layout");
    a_policy_label = new QLabel(centralwidget);
    a_policy_label->setObjectName("a_policy_label");
    a_policy_label->setFont(font3);

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
    b_changel_label->setFont(font2);

    b_vertical_layout->addWidget(b_changel_label, 0, Qt::AlignmentFlag::AlignHCenter);

    b_line_input = new QLineEdit(centralwidget);
    b_line_input->setObjectName("b_line_input");

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
    b_settings_title->setFont(font2);

    b_vertical_layout->addWidget(b_settings_title, 0, Qt::AlignmentFlag::AlignHCenter);

    b_runner_layout = new QHBoxLayout();
    b_runner_layout->setObjectName("b_runner_layout");
    b_runner_label = new QLabel(centralwidget);
    b_runner_label->setObjectName("b_runner_label");
    b_runner_label->setFont(font3);

    b_runner_layout->addWidget(b_runner_label);

    b_runner_input = new QLineEdit(centralwidget);
    b_runner_input->setObjectName("b_runner_input");

    b_runner_layout->addWidget(b_runner_input);

    b_runner_button = new QPushButton(centralwidget);
    b_runner_button->setObjectName("b_runner_button");

    b_runner_layout->addWidget(b_runner_button);

    b_vertical_layout->addLayout(b_runner_layout);

    horizontalLayout_6 = new QHBoxLayout();
    horizontalLayout_6->setObjectName("horizontalLayout_6");
    b_policy_label = new QLabel(centralwidget);
    b_policy_label->setObjectName("b_policy_label");
    b_policy_label->setFont(font3);

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
    c_change_label->setFont(font2);

    c_vertical_layout->addWidget(c_change_label, 0, Qt::AlignmentFlag::AlignHCenter);

    c_line_input = new QLineEdit(centralwidget);
    c_line_input->setObjectName("c_line_input");

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
    c_settings_title->setFont(font2);

    c_vertical_layout->addWidget(c_settings_title, 0,
                                 Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignVCenter);

    c_runner_layout = new QHBoxLayout();
    c_runner_layout->setObjectName("c_runner_layout");
    c_runner_label = new QLabel(centralwidget);
    c_runner_label->setObjectName("c_runner_label");
    c_runner_label->setFont(font3);

    c_runner_layout->addWidget(c_runner_label);

    c_runner_input = new QLineEdit(centralwidget);
    c_runner_input->setObjectName("c_runner_input");

    c_runner_layout->addWidget(c_runner_input);

    c_runner_button = new QPushButton(centralwidget);
    c_runner_button->setObjectName("c_runner_button");

    c_runner_layout->addWidget(c_runner_button);

    c_vertical_layout->addLayout(c_runner_layout);

    horizontalLayout_7 = new QHBoxLayout();
    horizontalLayout_7->setObjectName("horizontalLayout_7");
    c_policy_label = new QLabel(centralwidget);
    c_policy_label->setObjectName("c_policy_label");
    c_policy_label->setFont(font3);

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

    retranslateUi(MainWindow);

    QMetaObject::connectSlotsByName(MainWindow);
  }  // setupUi

  void retranslateUi(QMainWindow* MainWindow) {
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
    main_title->setText(QCoreApplication::translate("MainWindow", "A   <=   B   <=   C", nullptr));
    a_change_label->setText(
        QCoreApplication::translate("MainWindow",
                                    "\320\230\320\267\320\274\320\265\320\275\320\265\320\275\320\270\320\265 "
                                    "\320\267\320\275\320\260\321\207\320\265\320\275\320\270\321\217 A",
                                    nullptr));
    a_settings_title->setText(QCoreApplication::translate(
        "MainWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 A", nullptr));
    a_runner_label->setText(QCoreApplication::translate(
        "MainWindow", "\320\232\320\260\321\200\321\203\321\201\320\265\320\273\321\214", nullptr));
    a_runner_button->setText(QCoreApplication::translate(
        "MainWindow", "\320\227\320\260\320\277\321\203\321\201\321\202\320\270\321\202\321\214", nullptr));
    a_policy_label->setText(QCoreApplication::translate(
        "MainWindow", "\320\237\320\276\320\273\320\270\321\202\320\270\320\272\320\260", nullptr));
    b_changel_label->setText(
        QCoreApplication::translate("MainWindow",
                                    "\320\230\320\267\320\274\320\265\320\275\320\265\320\275\320\270\320\265 "
                                    "\320\267\320\275\320\260\321\207\320\265\320\275\320\270\321\217 B",
                                    nullptr));
    b_settings_title->setText(QCoreApplication::translate(
        "MainWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 B", nullptr));
    b_runner_label->setText(QCoreApplication::translate(
        "MainWindow", "\320\232\320\260\321\200\321\203\321\201\320\265\320\273\321\214", nullptr));
    b_runner_button->setText(QCoreApplication::translate(
        "MainWindow", "\320\227\320\260\320\277\321\203\321\201\321\202\320\270\321\202\321\214", nullptr));
    b_policy_label->setText(QCoreApplication::translate(
        "MainWindow", "\320\237\320\276\320\273\320\270\321\202\320\270\320\272\320\260", nullptr));
    c_change_label->setText(
        QCoreApplication::translate("MainWindow",
                                    "\320\230\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217 "
                                    "\320\267\320\275\320\260\321\207\320\265\320\275\320\270\321\217 C",
                                    nullptr));
    c_settings_title->setText(QCoreApplication::translate(
        "MainWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 C", nullptr));
    c_runner_label->setText(QCoreApplication::translate(
        "MainWindow", "\320\232\320\260\321\200\321\203\321\201\320\265\320\273\321\214", nullptr));
    c_runner_button->setText(QCoreApplication::translate(
        "MainWindow", "\320\227\320\260\320\277\321\203\321\201\321\202\320\270\321\202\321\214", nullptr));
    c_policy_label->setText(QCoreApplication::translate(
        "MainWindow", "\320\237\320\276\320\273\320\270\321\202\320\270\320\272\320\260", nullptr));
  }  // retranslateUi
};
