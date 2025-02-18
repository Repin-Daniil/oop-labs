#include <model.h>

namespace model {

DeepThought::DeepThought(int a, int b, int c) : a_(a), b_(b), c_(c) {
}

int DeepThought::Normalize(int value, int left, int right) {
  return std::min(right, std::max(value, left));
}

void DeepThought::IncrementNumber(Number number, int value) noexcept {
  UpdateNumber(number, GetNumber(number) + value);
}

void DeepThought::DecrementNumber(Number number, int value) noexcept {
  UpdateNumber(number, GetNumber(number) - value);
}

void DeepThought::UpdateNumber(Number number, int value) noexcept {
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

  update_lock.unlock();

  if (is_model_changed) {
    std::shared_lock notify_lock(numbers_mutex_);
    NotifyAll();
  }
}

bool DeepThought::UpdateA(int value, Policy policy) {
  policy = (policy != Policy::NONE ? policy : a_policy_);
  int normalized_value = Normalize(value, left_border_, right_border_);
  bool old_value = a_;

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
  bool old_value = b_;

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
  bool old_value = c_;

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

int DeepThought::GetNumber(Number number) const {
  std::shared_lock read_lock(numbers_mutex_);

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
  std::shared_lock read_lock(numbers_mutex_);

  return a_;
}

int DeepThought::GetB() const noexcept {
  std::shared_lock read_lock(numbers_mutex_);

  return b_;
}

int DeepThought::GetC() const noexcept {
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

}  // namespace model
