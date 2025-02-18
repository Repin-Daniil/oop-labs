#include "application.h"

namespace mvc::app {

Application::Application(std::string_view filename)
    : model_(infrastructure::LoadNumbers(filename)), storage_(model_, filename) {
  model_.AddObserver(&storage_);
}

model::DeepThought& Application::GetModel() noexcept {
  return model_;
}

void Application::StartRunner(model::DeepThought::Number number) {
  if (!runners_.contains(number)) {
    runners_.insert({number, Runner{model_, number}});
    runners_.at(number).Start();
  }
}

void Application::StopRunner(model::DeepThought::Number number) {
  runners_.erase(number);
}

}  // namespace mvc::app