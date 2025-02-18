#pragma once
#include "../infrastructure/storage/storage.h"
#include "runner/runner.h"


#include <unordered_map>

namespace mvc::app {

class Application {
public:
  explicit Application(std::string_view filename);
  model::DeepThought& GetModel() noexcept;
  void StartRunner(model::DeepThought::Number number);
  void StopRunner(model::DeepThought::Number number);

private:
  model::DeepThought model_;
  infrastructure::Storage storage_;
  std::unordered_map<model::DeepThought::Number, Runner> runners_;
};

} // app
