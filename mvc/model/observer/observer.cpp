#include "observer.hpp"

#include <memory>

void Subject::AddObserver(IListener* listener) {
  observers_.push_back(listener);
}

void Subject::NotifyAll() noexcept {
  for (auto& observer : observers_) {
    observer->OnChanged();
  }
}