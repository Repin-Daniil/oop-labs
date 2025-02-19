#pragma once

#include <QApplication>

#include <gui/form.hpp>
#include <utils/storage/storage.hpp>

namespace mvc::app {

class Application {
 public:
  explicit Application(std::string_view filename, int argc, char** argv);

  model::DeepThought& GetModel() noexcept;
  utils::run::Runners& GetRunners() noexcept;
  void Run();

 private:
  model::DeepThought model_;
  utils::serialization::Storage storage_;
  utils::run::Runners runners_;

  QApplication qt_app_;
  gui::Form form_;
};

}  // namespace mvc::app
