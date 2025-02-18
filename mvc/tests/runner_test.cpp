#define CATCH_CONFIG_MAIN
#include <atomic>
#include <chrono>
#include <thread>
#include "catch.hpp"

#include "../app/runner/runner.h"
#include "../infrastructure/log/log.hpp"

#include <infrastructure/log/log.hpp>

namespace mvc {
using namespace mvc::app;
using namespace mvc::model;

TEST_CASE("Runner starts, runs, and stops correctly", "[Runner]") {
  infrastructure::log::SetLogLevel(infrastructure::log::LogLevel::OFF);
  DeepThought model{10, 20, 30};
  auto test_number = DeepThought::Number::C;

  Runner runner(model, test_number);

  std::array<int, 10> log_arr;
  log_arr[0] = model.GetNumber(test_number);

  runner.Start();

  for (std::size_t i = 1; i < log_arr.size(); ++i) {
    LOG_INFO() << "GetNumber in TEST CASE";
    log_arr[i] = model.GetNumber(test_number);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  runner.Stop();


  int sum = 0;

  for (std::size_t i = 1; i < log_arr.size(); ++i) {
    sum += (log_arr[i] != log_arr[i - 1]);
  }

  CHECK(sum > 5);
}

TEST_CASE("Runner stops if not started", "[Runner]") {
  infrastructure::log::SetLogLevel(infrastructure::log::LogLevel::OFF);
  DeepThought model{10, 20, 30};
  auto test_number = DeepThought::Number::B;

  Runner runner(model, test_number);

  CHECK_NOTHROW(runner.Stop());
}

TEST_CASE("Runner does not double start", "[Runner]") {
  infrastructure::log::SetLogLevel(infrastructure::log::LogLevel::OFF);
  DeepThought model{10, 20, 30};
  auto test_number = DeepThought::Number::A;

  Runner runner(model, test_number);
  runner.Start();
  CHECK_NOTHROW(runner.Start());

  runner.Stop();
}

TEST_CASE("Runner correctly moves", "[Runner]") {
  infrastructure::log::SetLogLevel(infrastructure::log::LogLevel::OFF);
  DeepThought model{10, 20, 30};
  auto test_number = DeepThought::Number::A;

  Runner runner1(model, test_number);
  runner1.Start();

  Runner runner2(std::move(runner1));
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  runner2.Stop();
}

TEST_CASE("Runner correctly run after move", "[Runner]") {
  infrastructure::log::SetLogLevel(infrastructure::log::LogLevel::OFF);
  DeepThought model{10, 20, 30};
  auto test_number = DeepThought::Number::A;

  Runner runner1(model, test_number);
  Runner runner2(std::move(runner1));
  runner1.Start();
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  runner2.Stop();
  runner1.Stop();
}


TEST_CASE("Runner thread actually runs", "[Runner]") {
  infrastructure::log::SetLogLevel(infrastructure::log::LogLevel::OFF);
  DeepThought model{10, 20, 30};
  auto test_number = DeepThought::Number::A;

  Runner runner(model, test_number);

  runner.Start();
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  runner.Stop();
}

}  // namespace mvc
