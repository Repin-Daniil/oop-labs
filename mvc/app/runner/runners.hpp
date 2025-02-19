#pragma once
#include <app/runner/runner.hpp>
#include <model.hpp>
#include <unordered_map>

namespace mvc::app {
class Runner;

class Runners {
 public:
  explicit Runners(model::DeepThought& model);
  void StartRunner(model::DeepThought::Number number);
  void StopRunner(model::DeepThought::Number number);
  bool IsRunning(model::DeepThought::Number number) const;

 private:
  model::DeepThought& model_;
  std::unordered_map<model::DeepThought::Number, Runner> runners_;
};

}  // namespace mvc::app
