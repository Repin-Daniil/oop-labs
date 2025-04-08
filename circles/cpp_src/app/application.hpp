#pragma once

#include <QApplication>

#include <circles.hpp>
#include <view/form/form.hpp>

// TODO Сделать хранилище для сериализации #include <utils/storage/storage.hpp>

namespace circles::app {

class Application {
 public:
  explicit Application(std::string_view filename, int argc, char** argv);

  model::Circles& GetModel() noexcept;

  void Run();

 private:
  model::Circles model_;
  //  utils::serialization::Storage storage_;

  QApplication qt_app_;
  view::Form form_;
};

}  // namespace circles::app
