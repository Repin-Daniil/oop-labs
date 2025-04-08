#pragma once

#include <QtCore/qcoreapplication.h>

#include <QtCore/QVariant>
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

namespace mvc::view {

class NumbersUi {
 public:
  void setup(QMainWindow* MainWindow);

  QWidget* centralwidget{};
  QHBoxLayout* main_horizontal_layout{};
  QLabel* main_title{};
  QVBoxLayout* verticalLayout{};
  QSpacerItem* verticalSpacer_2{};

  QVBoxLayout* a_vertical_layout{};
  QLabel* a_change_label{};
  QLineEdit* a_line_input{};
  QSpinBox* a_spin_box{};
  QSlider* a_slider{};
  QProgressBar* a_progress_bar{};
  QSpacerItem* verticalSpacer_7{};
  QSpacerItem* verticalSpacer_6{};
  QSpacerItem* verticalSpacer_3{};
  QLabel* a_settings_title{};
  QHBoxLayout* a_runner_layout{};
  QLabel* a_runner_label{};
  QLineEdit* a_runner_input{};
  QPushButton* a_runner_button{};
  QHBoxLayout* a_policy_layout{};
  QLabel* a_policy_label{};
  QComboBox* a_policy_combo_box{};

  QVBoxLayout* b_vertical_layout{};
  QLabel* b_changel_label{};
  QLineEdit* b_line_input{};
  QSpinBox* b_spin_box{};
  QSlider* b_slider{};
  QProgressBar* b_progress_bar{};
  QSpacerItem* verticalSpacer_4{};
  QSpacerItem* verticalSpacer_9{};
  QSpacerItem* verticalSpacer_8{};
  QLabel* b_settings_title{};
  QHBoxLayout* b_runner_layout{};
  QLabel* b_runner_label{};
  QLineEdit* b_runner_input{};
  QPushButton* b_runner_button{};
  QHBoxLayout* horizontalLayout_6{};
  QLabel* b_policy_label{};
  QComboBox* b_policy_combo_box{};

  QVBoxLayout* c_vertical_layout{};
  QLabel* c_change_label{};
  QLineEdit* c_line_input{};
  QSpinBox* c_spin_box{};
  QSlider* c_slider{};
  QProgressBar* c_progress_bar{};
  QSpacerItem* verticalSpacer_5{};
  QSpacerItem* verticalSpacer_10{};
  QSpacerItem* verticalSpacer_12{};
  QSpacerItem* verticalSpacer_11{};
  QLabel* c_settings_title{};
  QHBoxLayout* c_runner_layout{};
  QLabel* c_runner_label{};
  QLineEdit* c_runner_input{};
  QPushButton* c_runner_button{};
  QHBoxLayout* horizontalLayout_7{};
  QLabel* c_policy_label{};
  QComboBox* c_policy_combo_box{};
  QSpacerItem* verticalSpacer{};
};

}  // namespace mvc::view
