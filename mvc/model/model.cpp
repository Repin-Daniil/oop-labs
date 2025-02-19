#include <model.hpp>

#include "../infrastructure/log/log.hpp"

namespace mvc::model {

DeepThought::DeepThought(int a, int b, int c) {
  if (a >= 0 && a <= b && b <= c && c <= 100) {
    a_ = a;
    b_ = b;
    c_ = c;
  } else {
    throw std::invalid_argument("Invalid arguments");
  }
}

DeepThought::DeepThought(const std::tuple<int, int, int>& numbers)
    : DeepThought(std::get<0>(numbers), std::get<1>(numbers), std::get<2>(numbers)) {
}

int DeepThought::Normalize(int value, int left, int right) {
  return std::min(right, std::max(value, left));
}

bool DeepThought::IncrementNumber(Number number, int value) noexcept {
  auto new_value = GetNumber(number) + value;
  return UpdateNumber(number, new_value);
}

bool DeepThought::DecrementNumber(Number number, int value) noexcept {
  auto new_value = GetNumber(number) - value;
  return UpdateNumber(number, new_value);
}

bool DeepThought::UpdateNumber(Number number, int value) noexcept {
  LOG_TRACE() << "UpdateNumber mutex unique lock (try)";
  std::unique_lock update_lock(numbers_mutex_);
  bool is_model_changed = false;

  switch (number) {
    case Number::A:
      is_model_changed = UpdateA(value);
      break;
    case Number::B:
      is_model_changed = UpdateB(value);
      break;
    case Number::C:
      is_model_changed = UpdateC(value);
      break;
  }

  LOG_TRACE() << "UpdateNumber mutex unique unlock (try)";
  update_lock.unlock();

  if (is_model_changed) {
    NotifyAll();
  }

  return is_model_changed;
}

bool DeepThought::UpdateA(int value, Policy policy) {
  policy = (policy != Policy::NONE ? policy : a_policy_);
  int normalized_value = Normalize(value, left_border_, right_border_);
  int old_value = a_;

  if (normalized_value != value) {
    if (policy == Policy::RESTRICTIVE) {
      value = normalized_value;
    } else if (policy == Policy::FORBIDDING || policy == Policy::PERMISSIVE) {
      return false;
    }
  }

  a_ = value;

  if (b_ < a_) {
    UpdateB(value, Policy::PERMISSIVE);
  }

  return a_ != old_value;
}

bool DeepThought::UpdateB(int value, Policy policy) {
  policy = (policy != Policy::NONE ? policy : b_policy_);
  int old_value = b_;

  if (policy == Policy::PERMISSIVE) {
    b_ = value;

    if (c_ < b_) {
      UpdateC(value);
    } else if (a_ > b_) {
      UpdateA(value);
    }
  } else if (policy == Policy::RESTRICTIVE) {
    b_ = Normalize(value, a_, c_);
  } else if (policy == Policy::FORBIDDING) {
    b_ = ((a_ <= value && value <= c_) ? value : b_);
  }

  return b_ != old_value;
}

bool DeepThought::UpdateC(int value, Policy policy) {
  policy = (policy != Policy::NONE ? policy : c_policy_);
  int normalized_value = Normalize(value, left_border_, right_border_);
  int old_value = c_;

  if (normalized_value != value) {
    if (policy == Policy::RESTRICTIVE) {
      value = normalized_value;
    } else if (policy == Policy::FORBIDDING || policy == Policy::PERMISSIVE) {
      return false;
    }
  }

  c_ = value;

  if (b_ > c_) {
    UpdateB(value, Policy::PERMISSIVE);
  }

  return c_ != old_value;
}

std::tuple<int, int, int> DeepThought::GetNumbers() const noexcept {
  LOG_TRACE() << "GetNumbers shared lock (try)";
  std::shared_lock lock(numbers_mutex_);

  return {a_, b_, c_};
}

int DeepThought::GetNumber(Number number) const {
  switch (number) {
    case Number::A:
      return GetA();

    case Number::B:
      return GetB();

    case Number::C:
      return GetC();
  }

  throw std::invalid_argument("Number does not exist");
}

int DeepThought::GetA() const noexcept {
  LOG_TRACE() << "GetA mutex shared lock (try)";
  std::shared_lock read_lock(numbers_mutex_);

  return a_;
}

int DeepThought::GetB() const noexcept {
  LOG_TRACE() << "GetB mutex shared lock (try)";
  std::shared_lock read_lock(numbers_mutex_);

  return b_;
}

int DeepThought::GetC() const noexcept {
  LOG_TRACE() << "GetC mutex shared lock (try)";
  std::shared_lock read_lock(numbers_mutex_);

  return c_;
}

int DeepThought::GetLeftBorder() const noexcept {
  return left_border_;
}

int DeepThought::GetRightBorder() const noexcept {
  return right_border_;
}

void DeepThought::SetPolicy(Number number, Policy policy) noexcept {
  LOG_TRACE() << "SetPolicy mutex unique lock (try)";
  std::unique_lock policy_lock(numbers_mutex_);

  if (policy == Policy::PERMISSIVE) {
    return;
  }

  switch (number) {
    case Number::A:
      a_policy_ = policy;
      break;

    case Number::B:
      b_policy_ = policy;
      break;

    case Number::C:
      c_policy_ = policy;
      break;
  }
}

DeepThought::Policy DeepThought::GetPolicy(Number number) const noexcept {
  LOG_TRACE() << "GetPolicy mutex shared lock (try)";
  std::shared_lock read_lock(numbers_mutex_);

  switch (number) {
    case Number::A:
      return a_policy_;

    case Number::B:
      return b_policy_;

    case Number::C:
      return c_policy_;
  }

  throw std::invalid_argument("Number does not exist");
}

int DeepThought::GetAnswerOnAnyQuestion() const noexcept {
  return ultimate_answer_;
}

}  // namespace mvc::model
