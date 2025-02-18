#pragma once
#include <model/model.hpp>
#include <thread>

namespace mvc::app {

class Runner {
 public:
  Runner() = delete;
  Runner(model::DeepThought& model, model::DeepThought::Number number);
  Runner(const Runner& runner) = delete;
  Runner(Runner&& runner) noexcept;

  Runner& operator=(const Runner&) = delete;
  Runner& operator=(Runner&& runner) = delete;

  void Start();
  void Stop();

  ~Runner();

 private:
  model::DeepThought& model_;
  model::DeepThought::Number number_;

  std::unique_ptr<std::atomic<bool>> running_{new std::atomic(false)};
  std::thread thread_{};
};

}  // namespace mvc::app