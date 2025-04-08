#pragma once

#include <QtWidgets/QApplication>
#include <observer.hpp>
#include <utils/runner/runners.hpp>
#include <view/ui.hpp>

namespace mvc::view {

class Form : public QMainWindow, public IListener {
  Q_OBJECT

 public:
  Form(model::DeepThought& model, utils::run::Runners& runners, QWidget* parent = nullptr);
  void OnChanged() noexcept override;

 private:
  model::DeepThought& model_;
  utils::run::Runners& runners_;

  NumbersUi ui_{};
};

}  // namespace mvc::gui
