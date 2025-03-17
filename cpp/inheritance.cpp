#include <execinfo.h>
#include <cstdlib>

#include <symcpp/utils/log.hpp>

struct SuperBase {
  SuperBase() {
    LOG_DEBUG() << "SuperBase default";
  }

  explicit SuperBase(SuperBase* obj) {
    LOG_DEBUG() << "SuperBase ptr ctor";
  }

  SuperBase(SuperBase& obj) {
    LOG_DEBUG() << "SuperBase ref ctor";
  }

  ~SuperBase() {
    LOG_DEBUG() << "SuperBase dtor";
  }
};

struct Base : SuperBase {
  Base() {
    LOG_DEBUG() << "Base default";
  }

  explicit Base(Base* obj) {
    LOG_DEBUG() << "Base ptr ctor";
  }

  Base(Base& obj) {
    LOG_DEBUG() << "Base ref ctor";
  }

  ~Base() {
    LOG_DEBUG() << "Base dtor";
  }
};

struct Derived : Base {
  Derived() {
    LOG_DEBUG() << "Derived default";
  }

  explicit Derived(Derived* obj) {
    LOG_DEBUG() << "Derived ptr ctor";
  }

  Derived(Derived& obj) {
    LOG_DEBUG() << "Derived ref ctor";
  }

  ~Derived() {
    LOG_DEBUG() << "Derived dtor";
  }
};

void func1(Base obj) {
}

void func2(Base* obj) {
}

void func3(Base& obj) {
}

int main() {
  SetLogLevel(symcpp::utils::log::LogLevel::DEBUG);
  symcpp::utils::log::SetLogLocationEnabled(false);
  symcpp::utils::log::SetLogTimeEnabled(false);

  Derived d;

  return 0;
}
