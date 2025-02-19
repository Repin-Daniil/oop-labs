#define CATCH_CONFIG_MAIN
#include <atomic>
#include <chrono>
#include <thread>
#include "catch.hpp"

#include <utils/runner/runner.hpp>
#include <utils/runner/runner.hpp>  // check include guards

#include <log.hpp>

namespace mvc {
using namespace mvc::utils::run;
using namespace mvc::model;

TEST_CASE("Runner starts, runs, and stops correctly", "[Runner]") {
  SetLogLevel(utils::log::LogLevel::OFF);
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
  CHECK(runner.IsRunning());
  runner.Stop();
  CHECK(!runner.IsRunning());

  int sum = 0;

  for (std::size_t i = 1; i < log_arr.size(); ++i) {
    sum += (log_arr[i] != log_arr[i - 1]);
  }

  CHECK(sum > 5);
}

TEST_CASE("Runner stops if not started", "[Runner]") {
  SetLogLevel(utils::log::LogLevel::OFF);
  DeepThought model{10, 20, 30};
  auto test_number = DeepThought::Number::B;

  Runner runner(model, test_number);
  CHECK(!runner.IsRunning());
  CHECK_NOTHROW(runner.Stop());
}

TEST_CASE("Runner does not double start", "[Runner]") {
  SetLogLevel(utils::log::LogLevel::OFF);
  DeepThought model{10, 20, 30};
  auto test_number = DeepThought::Number::A;

  Runner runner(model, test_number);
  CHECK(!runner.IsRunning());
  runner.Start();
  CHECK_NOTHROW(runner.Start());
  CHECK(runner.IsRunning());
  runner.Stop();
  CHECK(!runner.IsRunning());
}

TEST_CASE("Runner correctly moves", "[Runner]") {
  SetLogLevel(utils::log::LogLevel::OFF);
  DeepThought model{10, 20, 30};
  auto test_number = DeepThought::Number::A;

  Runner runner1(model, test_number);
  CHECK(!runner1.IsRunning());
  runner1.Start();
  CHECK(runner1.IsRunning());

  Runner runner2(std::move(runner1));
  CHECK(!runner1.IsRunning());
  CHECK(runner2.IsRunning());
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  CHECK(runner2.IsRunning());
  runner2.Stop();
  CHECK(!runner2.IsRunning());
}

TEST_CASE("Runner correctly run after move", "[Runner]") {
  SetLogLevel(utils::log::LogLevel::OFF);
  DeepThought model{10, 20, 30};
  auto test_number = DeepThought::Number::A;

  Runner runner1(model, test_number);
  CHECK(!runner1.IsRunning());
  Runner runner2(std::move(runner1));
  CHECK(!runner2.IsRunning());
  CHECK(!runner1.IsRunning());
  runner1.Start();
  CHECK(runner1.IsRunning());
  CHECK(!runner2.IsRunning());
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  CHECK(runner1.IsRunning());
  CHECK(!runner2.IsRunning());
  runner2.Stop();
  runner1.Stop();
  CHECK(!runner1.IsRunning());
  CHECK(!runner2.IsRunning());
}

TEST_CASE("Runner thread actually runs", "[Runner]") {
  SetLogLevel(utils::log::LogLevel::OFF);
  DeepThought model{10, 20, 30};
  auto test_number = DeepThought::Number::A;

  Runner runner(model, test_number);
  CHECK(!runner.IsRunning());

  runner.Start();
  CHECK(runner.IsRunning());

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  runner.Stop();
  CHECK(!runner.IsRunning());
}

}  // namespace mvc
