#pragma once

#include <memory>
#include <vector>

class IListener {
 public:
  virtual void OnChanged() noexcept = 0;

  virtual ~IListener() = default;
};

class Subject {
 public:
  void AddObserver(IListener* listener);

 protected:
  void NotifyAll() noexcept;

  ~Subject() = default;  // https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-dtor-virtual

 private:
  std::vector<IListener*> observers_;
};
