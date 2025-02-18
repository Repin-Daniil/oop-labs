#pragma once

#ifdef ERROR
#undef ERROR
#endif

#ifdef DEBUG
#undef DEBUG
#endif

#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <source_location>
#include <sstream>

namespace mvc::infrastructure::log {

struct BashColors {
  constexpr static const char* RESET = "\033[0m";
  constexpr static const char* RED = "\033[31m";
  constexpr static const char* YELLOW = "\033[33m";
  constexpr static const char* BLUE = "\033[34m";
  constexpr static const char* CYAN = "\033[36m";
  constexpr static const char* GREEN = "\033[32m";
  constexpr static const char* MAGENTA = "\033[35m";
};

enum class LogLevel {
  TRACE,
  DEBUG,
  INFO,
  WARNING,
  ERROR,
  CRITICAL,
  OFF,
};

using LogCallback = std::function<void(LogLevel, std::string_view)>;

LogCallback& GetLogger();
void SetLogger(LogCallback newLogger);

LogLevel GetLogLevel();
bool GetLogTimeEnabled();
bool GetLogLocationEnabled();
bool GetThreadSyncEnabled();

void SetLogLevel(LogLevel level);
void SetLogTimeEnabled(bool enabled);
void SetLogLocationEnabled(bool enabled);
void SetThreadSyncEnabled(bool enabled);

class LogStream {
  static auto GetTimestamp();

 public:
  explicit LogStream(LogLevel level, std::source_location loc = std::source_location::current());

  template <typename T>
  LogStream& operator<<(const T& value) {
    buffer_ << value;
    return *this;
  }

  ~LogStream();

 private:
  static const char* GetLogLevelName(LogLevel level);
  static const char* GetLogLevelColor(LogLevel level);

  LogLevel level_;
  std::ostringstream buffer_;
  std::source_location location_;
};

#define LOG(level)                                                              \
  if (mvc::infrastructure::log::LogLevel::level >= mvc::infrastructure::log::GetLogLevel()) \
  mvc::infrastructure::log::LogStream(mvc::infrastructure::log::LogLevel::level, std::source_location::current())

#define LOG_TRACE() LOG(TRACE)
#define LOG_DEBUG() LOG(DEBUG)
#define LOG_INFO() LOG(INFO)
#define LOG_WARNING() LOG(WARNING)
#define LOG_ERROR() LOG(ERROR)
#define LOG_CRITICAL() LOG(CRITICAL)

}  // namespace symcpp::utils::log
