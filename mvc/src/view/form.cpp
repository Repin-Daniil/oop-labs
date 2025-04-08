#include "form.hpp"

namespace mvc::view {

Form::Form(model::DeepThought& model, utils::run::Runners& runners, QWidget* parent)
    : model_(model), runners_(runners), QMainWindow(parent) {
  ui_.setup(this);

  ui_.a_policy_combo_box->addItem("Forbidding", QVariant::fromValue(model::DeepThought::Policy::FORBIDDING));
  ui_.a_policy_combo_box->addItem("Restrictive", QVariant::fromValue(model::DeepThought::Policy::RESTRICTIVE));
  ui_.b_policy_combo_box->addItem("Forbidding", QVariant::fromValue(model::DeepThought::Policy::FORBIDDING));
  ui_.b_policy_combo_box->addItem("Restrictive", QVariant::fromValue(model::DeepThought::Policy::RESTRICTIVE));
  ui_.c_policy_combo_box->addItem("Forbidding", QVariant::fromValue(model::DeepThought::Policy::FORBIDDING));
  ui_.c_policy_combo_box->addItem("Restrictive", QVariant::fromValue(model::DeepThought::Policy::RESTRICTIVE));

  connect(ui_.a_spin_box, qOverload<int>(&QSpinBox::valueChanged), this, [this](int value) {
    if (!model_.UpdateNumber(model::DeepThought::Number::A, value)) ui_.a_spin_box->setValue(model_.GetA());
  });
  connect(ui_.b_spin_box, qOverload<int>(&QSpinBox::valueChanged), this, [this](int value) {
    if (!model_.UpdateNumber(model::DeepThought::Number::B, value)) ui_.b_spin_box->setValue(model_.GetB());
  });
  connect(ui_.c_spin_box, qOverload<int>(&QSpinBox::valueChanged), this, [this](int value) {
    if (!model_.UpdateNumber(model::DeepThought::Number::C, value)) ui_.c_spin_box->setValue(model_.GetC());
  });

  connect(ui_.a_slider, &QSlider::valueChanged, this, [this](int value) {
    if (!model_.UpdateNumber(model::DeepThought::Number::A, value)) ui_.a_slider->setValue(model_.GetA());
  });
  connect(ui_.b_slider, &QSlider::valueChanged, this, [this](int value) {
    if (!model_.UpdateNumber(model::DeepThought::Number::B, value)) ui_.b_slider->setValue(model_.GetB());
  });
  connect(ui_.c_slider, &QSlider::valueChanged, this, [this](int value) {
    if (!model_.UpdateNumber(model::DeepThought::Number::C, value)) ui_.c_spin_box->setValue(model_.GetC());
  });

  connect(ui_.a_line_input, &QLineEdit::editingFinished, this, [this]() {
    bool ok;
    int value = ui_.a_line_input->text().toInt(&ok);
    if (!ok || !model_.UpdateNumber(model::DeepThought::Number::A, value))
      ui_.a_line_input->setText(QString::number(model_.GetA()));
  });
  connect(ui_.b_line_input, &QLineEdit::editingFinished, this, [this]() {
    bool ok;
    int value = ui_.b_line_input->text().toInt(&ok);
    if (!ok || !model_.UpdateNumber(model::DeepThought::Number::B, value))
      ui_.b_line_input->setText(QString::number(model_.GetB()));
  });
  connect(ui_.c_line_input, &QLineEdit::editingFinished, this, [this]() {
    bool ok;
    int value = ui_.c_line_input->text().toInt(&ok);
    if (!ok || !model_.UpdateNumber(model::DeepThought::Number::C, value))
      ui_.c_line_input->setText(QString::number(model_.GetC()));
  });

  connect(ui_.a_runner_button, &QPushButton::clicked, this, [this]() {
    if (runners_.IsRunning(model::DeepThought::Number::A)) {
      runners_.StopRunner(model::DeepThought::Number::A);
      ui_.a_runner_button->setText("Запустить");
    } else {
      runners_.StartRunner(model::DeepThought::Number::A);
      ui_.a_runner_button->setText("Остановить");
    }
  });

  connect(ui_.b_runner_button, &QPushButton::clicked, this, [this]() {
    if (runners_.IsRunning(model::DeepThought::Number::B)) {
      runners_.StopRunner(model::DeepThought::Number::B);
      ui_.b_runner_button->setText("Запустить");
    } else {
      runners_.StartRunner(model::DeepThought::Number::B);
      ui_.b_runner_button->setText("Остановить");
    }
  });

  connect(ui_.c_runner_button, &QPushButton::clicked, this, [this]() {
    if (runners_.IsRunning(model::DeepThought::Number::C)) {
      runners_.StopRunner(model::DeepThought::Number::C);
      ui_.c_runner_button->setText("Запустить");
    } else {
      runners_.StartRunner(model::DeepThought::Number::C);
      ui_.c_runner_button->setText("Остановить");
    }
  });

  connect(ui_.a_policy_combo_box, &QComboBox::currentIndexChanged, this, [this]() {
    auto selected_policy = ui_.a_policy_combo_box->currentData().value<model::DeepThought::Policy>();
    model_.SetPolicy(model::DeepThought::Number::A, selected_policy);
  });

  connect(ui_.b_policy_combo_box, &QComboBox::currentIndexChanged, this, [this]() {
    auto selected_policy = ui_.b_policy_combo_box->currentData().value<model::DeepThought::Policy>();
    model_.SetPolicy(model::DeepThought::Number::B, selected_policy);
  });
  connect(ui_.c_policy_combo_box, &QComboBox::currentIndexChanged, this, [this]() {
    auto selected_policy = ui_.c_policy_combo_box->currentData().value<model::DeepThought::Policy>();
    model_.SetPolicy(model::DeepThought::Number::C, selected_policy);
  });
}

void Form::OnChanged() noexcept {
  QMetaObject::invokeMethod(
      this,
      [this]() {
        auto [a, b, c] = model_.GetNumbers();

        ui_.a_spin_box->setValue(a);
        ui_.b_spin_box->setValue(b);
        ui_.c_spin_box->setValue(c);

        ui_.a_slider->setValue(a);
        ui_.b_slider->setValue(b);
        ui_.c_slider->setValue(c);

        ui_.a_progress_bar->setValue(a);
        ui_.b_progress_bar->setValue(b);
        ui_.c_progress_bar->setValue(c);

        ui_.a_line_input->setText(QString::number(a));
        ui_.b_line_input->setText(QString::number(b));
        ui_.c_line_input->setText(QString::number(c));
      },
      Qt::QueuedConnection);
  }
}  // namespace mvc::view
