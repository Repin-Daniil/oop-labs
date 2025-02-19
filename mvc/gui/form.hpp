#pragma once

#include "ui.hpp"

#include <QtWidgets/QApplication>
#include <app/runner/runners.hpp>

#include <observer/observer.hpp>

namespace mvc::gui {

class Form : public QMainWindow, public IListener {
  Q_OBJECT

 // private slots:
 //  void updateResult();

 public:
  Form(model::DeepThought& model, app::Runners& runners, QWidget* parent = nullptr);
  void OnChanged() noexcept override;

 private:
  model::DeepThought& model_;
  app::Runners& runners_;

  NumbersUi ui_{};
};

}  // namespace mvc::gui
