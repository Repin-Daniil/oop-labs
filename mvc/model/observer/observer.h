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
  void AddObserver(std::shared_ptr<IListener> listener);

protected:
  void NotifyAll() noexcept;

  ~Subject() = default;  // https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-dtor-virtual

private:
  std::vector<std::shared_ptr<IListener> > observers_;
  //FIXME Идея с shared_ptr-ами не очень, получается, что модель владеет инфраструкторой? Наверное, это Application должно все разруливать
};
