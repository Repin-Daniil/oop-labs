#pragma once
#include <unordered_map>

#include <model.hpp>
#include <utils/runner/runner.hpp>

namespace mvc::utils::run {
class Runner;

class Runners {
 public:
  explicit Runners(model::DeepThought& model);
  void StartRunner(model::DeepThought::Number number);
  void StopRunner(model::DeepThought::Number number);
  [[nodiscard]] bool IsRunning(model::DeepThought::Number number) const;

 private:
  model::DeepThought& model_;
  std::unordered_map<model::DeepThought::Number, Runner> runners_;
};

}  // namespace mvc::utils::run
