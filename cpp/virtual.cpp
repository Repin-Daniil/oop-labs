#include <symcpp/utils/log.hpp>

struct Base {
  virtual void MagicMethod() {
    LOG_INFO() << "Base with magic";
  }

  void NonMagicMethod() {
    LOG_INFO() << "Base non magic";
    MagicMethod();
  }

  virtual ~Base() = default;
};

struct Derived : public Base {
  void MagicMethod() override {
    LOG_INFO() << "Derived with magic";
  }

  void NonMagicMethod() {
    LOG_INFO() << "Derived non magic";
  }
};

int main() {
  symcpp::utils::log::SetLogTimeEnabled(false);
  symcpp::utils::log::SetLogLocationEnabled(false);

  // std::shared_ptr<Derived> derived = std::make_shared<Derived>();
  // std::shared_ptr<Base> base = std::make_shared<Derived>();

  // base->MagicMethod();
  // base->NonMagicMethod();
  // derived->MagicMethod();
  // derived->NonMagicMethod();

  return EXIT_SUCCESS;
}
