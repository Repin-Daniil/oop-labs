#include "runner.hpp"

#include <infrastructure/log/log.hpp>

namespace mvc::app {

static void Run(model::DeepThought& model, model::DeepThought::Number number, const std::atomic<bool>& running) {
  bool grow = true;

  while (running) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    if (grow) {
      grow = model.IncrementNumber(number, 1);
      LOG_TRACE() << "INCREMENT " << model.GetNumber(number);
    } else {
      grow = !model.DecrementNumber(number, 1);
      LOG_TRACE() << "DECREMENT " << model.GetNumber(number);
    }
  }
}

Runner::Runner(model::DeepThought& model, model::DeepThought::Number number) : model_(model), number_(number) {
  LOG_TRACE() << "Runner::Runner()";
}

Runner::Runner(Runner&& runner) noexcept
    : model_(runner.model_),
      number_(runner.number_),
      running_(std::move(runner.running_)),
      thread_(std::move(runner.thread_)) {
  LOG_TRACE() << "Runner::Runner(Runner&&)";
}

void Runner::Start() {
  if(!running_) {
    running_ = std::make_unique<std::atomic<bool>>(false);
  }

  if (*running_) {
    return;
  }

  LOG_DEBUG() << "Start runner for number ";
  *running_ = true;
  LOG_TRACE() << "Set atomic to true";
  thread_ = std::move(std::thread{Run, std::ref(model_), number_, std::ref(*running_)});
  LOG_INFO() << "Runner for number start";
}

void Runner::Stop() {
  if (!running_) {
    return;
  }
  LOG_DEBUG() << "Stop runner for number ";
  if (thread_.joinable()) {
    LOG_TRACE() << "Set atomic to false";
    *running_ = false;
    LOG_TRACE() << "Join thread";
    thread_.join();
    LOG_INFO() << "Runner stopped";
  } else {
    if (*running_) {
      LOG_DEBUG() << "Runner has been already stopping";
    } else {
      LOG_DEBUG() << "Runner has already been stopped";
    }
  }
}

bool Runner::IsRunning() const {
  return running_ && *running_ && thread_.joinable(); //fixme дописать тесты
}

Runner::~Runner() {
  LOG_TRACE() << "Runner::~Runner()";
  Stop();
}

}  // namespace mvc::app
