#pragma once

#include <QApplication>

#include <infrastructure/storage/storage.hpp>
#include <gui/form.hpp>

namespace mvc::app {

class Application : std::enable_shared_from_this<Application> {
public:
  explicit Application(std::string_view filename, int argc, char **argv);

  model::DeepThought& GetModel() noexcept;
  Runners& GetRunners() noexcept;
  void Run();


private:
  model::DeepThought model_;
  infrastructure::Storage storage_;
  Runners runners_;
  gui::Form form_;
};

} // app
