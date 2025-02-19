#include "application.hpp"

namespace mvc::app {

Application::Application(std::string_view filename, int argc, char** argv)
    : model_(infrastructure::LoadNumbers(filename)),
      storage_(model_, filename),
      runners_(model_),
      qt_app_(argc, argv),
      form_(model_, runners_) {
  model_.AddObserver(&storage_);
  model_.AddObserver(&form_);
}

void Application::Run() {
  form_.OnChanged();
  form_.show();
  QApplication::exec();
}

model::DeepThought& Application::GetModel() noexcept {
  return model_;
}

}  // namespace mvc::app
