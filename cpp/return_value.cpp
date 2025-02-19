#include <execinfo.h>
#include <cstdlib>

#include <symcpp/utils/log.hpp>

struct Base {
  int c = 2;

  Base() {
    LOG_DEBUG() << "Base default";
  }

  Base(Base&&) = delete;

  Base(Base& obj) {
    LOG_DEBUG() << "Base ref ctor";
  }

  Base(Base* obj) {  // NOLINT
    LOG_DEBUG() << "Base ptr ctor";
  }

  ~Base() {
    LOG_DEBUG() << "Base dtor";
  }
};

struct Derived : Base {
  Derived() {
    LOG_DEBUG() << "Derived default";
  }

  Derived(Derived&&) = delete;

  explicit Derived(Derived* obj) {
    LOG_DEBUG() << "Derived ptr ctor";
  }

  explicit Derived(Derived& obj) {
    LOG_DEBUG() << "Derived ref ctor";
  }

  ~Derived() {
    LOG_DEBUG() << "Derived dtor";
  }
};

Base func1() {
  Base b;

  return {b};
}

Base* func2() {
  Base b;

  return &b;
}

Base& func3() {
  Base b;

  return b;
}

Base func4() {
  auto b = new Base;

  return *b;
}

Base* func5() {
  Base* b = new Base;

  return b;
}

Base& func6() {
  auto b = new Base;

  return *b;
}

int main() {
  symcpp::utils::log::SetLogLevel(symcpp::utils::log::LogLevel::DEBUG);
  symcpp::utils::log::SetLogLocationEnabled(false);
  symcpp::utils::log::SetLogTimeEnabled(false);

  Base b = func2();

  return 0;
}
