#include <execinfo.h>
#include <cstdlib>

#include <iostream>
#include <symcpp/utils/log.hpp>

class Shape {
 public:
  Shape(int i) {  // NOLINT
    std::cout << "Shape(i)" << i;
  }
};

void PrintStackTrace() {
  constexpr int max_frames = 64;
  void* buffer[max_frames];
  int numFrames = backtrace(buffer, max_frames);
  char** symbols = backtrace_symbols(buffer, numFrames);

  if (symbols) {
    symcpp::utils::log::LogStream output{symcpp::utils::log::LogLevel::TRACE, std::source_location::current()};
    for (int i = 0; i < numFrames; i++) {
      output << "\n" << symbols[i];
    }
    free(symbols);
  }
}

struct SuperBase {
  Shape shapeInSuperbase{1};
  SuperBase() {
    LOG_INFO() << "SuperBase";
    PrintStackTrace();
  }
};

struct Base : SuperBase {
  Shape shapeInBase{2};
  int x{2};

  Base() : x{3}, SuperBase() {
    LOG_INFO() << "Base";
    PrintStackTrace();
  }
};

struct Derived : Base {
  Derived() {
    LOG_INFO() << "Derived";
    PrintStackTrace();
  }
};

int main() {
  // https://isocpp.org/wiki/faq/multiple-inheritance#mi-vi-ctor-order
  symcpp::utils::log::SetLogLevel(symcpp::utils::log::LogLevel::TRACE);

  Derived d;

  return 0;
}
