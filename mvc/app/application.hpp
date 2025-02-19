#pragma once

#include <QApplication>

#include <gui/form.hpp>
#include <infrastructure/storage/storage.hpp>

namespace mvc::app {

class Application {
 public:
  explicit Application(std::string_view filename, int argc, char** argv);

  model::DeepThought& GetModel() noexcept;
  Runners& GetRunners() noexcept;
  void Run();

 private:
  model::DeepThought model_;
  infrastructure::Storage storage_;
  Runners runners_;

  QApplication qt_app_;
  gui::Form form_;
};

}  // namespace mvc::app
