#include "../third_party/logger/log.hpp"

#include <execinfo.h>
#include <cstdlib>

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
  int x = 2;

  SuperBase() {
    LOG_INFO() << "SuperBase";
    PrintStackTrace();

  }

  SuperBase(SuperBase *obj) {

  }

  SuperBase(SuperBase &obj) {

  }

  ~SuperBase() {

  }


};


struct Base : SuperBase {
  int x{2};
  Base() : x{3},
  SuperBase() {
    LOG_INFO() << "Base";
    PrintStackTrace();

  }

  Base(Base *obj) {

  }

  Base(Base &obj) {

  }

  ~Base() {

  }


};


struct Derived : Base {

  Derived() {
    LOG_INFO() << "Derived";
    PrintStackTrace();
  }

  Derived(Derived *obj) {

  }

  Derived(Derived &obj) {

  }

  ~Derived() {

  }
};


void func1(Base obj) {

};

void func2(Base *obj) {

};

void func3(Base obj) {

};

int main() {
  // https://isocpp.org/wiki/faq/multiple-inheritance#mi-vi-ctor-order
  symcpp::utils::log::SetLogLevel(symcpp::utils::log::LogLevel::TRACE);

  Derived d;

  return 0;
}
