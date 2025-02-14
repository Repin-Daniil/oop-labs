#include <model.h>

namespace model {

DeepThought::DeepThought(int a, int b, int c) : a_(a), b_(b), c_(c) {
}

int DeepThought::Normalize(int value, int left, int right) {
  return std::min(right, std::max(value, left));
}

void DeepThought::UpdateNumber(Number number, int value) noexcept {
  std::unique_lock update_lock(numbers_mutex_);

  switch (number) {
    case Number::A:
      UpdateA(value);
      break;
    case Number::B:
      UpdateB(value);
      break;
    case Number::C:
      UpdateC(value);
      break;
  }

  update_lock.unlock();
  std::shared_lock notify_lock(numbers_mutex_);

  NotifyAll();
}

void DeepThought::UpdateA(int value, Policy policy) {
  policy = (policy != Policy::NONE ? policy : a_policy_);
  int normalized_value = Normalize(value, left_border_, right_border_);

  if (normalized_value != value) {
    if (policy == Policy::RESTRICTIVE) {
      value = normalized_value;
    } else if (policy == Policy::FORBIDDING || policy == Policy::PERMISSIVE) {
      return;
    }
  }

  a_ = value;

  if (b_ < a_) {
    UpdateB(value, Policy::PERMISSIVE);
  }
}

void DeepThought::UpdateB(int value, Policy policy) {
  policy = (policy != Policy::NONE ? policy : b_policy_);

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
}

void DeepThought::UpdateC(int value, Policy policy) {
  policy = (policy != Policy::NONE ? policy : c_policy_);
  int normalized_value = Normalize(value, left_border_, right_border_);

  if (normalized_value != value) {
    if (policy == Policy::RESTRICTIVE) {
      value = normalized_value;
    } else if (policy == Policy::FORBIDDING || policy == Policy::PERMISSIVE) {
      return;
    }
  }

  c_ = value;

  if (b_ > c_) {
    UpdateB(value, Policy::PERMISSIVE);
  }
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
