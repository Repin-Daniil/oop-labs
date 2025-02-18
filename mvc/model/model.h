#pragma once

#include <observer/observer.h>
#include <shared_mutex>

namespace model {

/**
 *@brief Модель для работы с тремя целыми числами A, B, C
 *@invariant 0 <= A <= B <= C <= 100
 *@author Repin-Daniil <daniil.r4@yandex.ru>
 */
class DeepThought : public Subject {
 public:
  enum class Number { A, B, C };
  enum class Policy { NONE, RESTRICTIVE, FORBIDDING, PERMISSIVE };

  DeepThought() = default;
  DeepThought(int a, int b, int c);

  void UpdateNumber(Number number, int value) noexcept;
  void IncrementNumber(Number number, int value) noexcept;
  void DecrementNumber(Number number, int value) noexcept;

  [[nodiscard]] int GetNumber(Number number) const;
  [[nodiscard]] int GetAnswerOnAnyQuestion() const noexcept;
  [[nodiscard]] int GetA() const noexcept;
  [[nodiscard]] int GetB() const noexcept;
  [[nodiscard]] int GetC() const noexcept;

  [[nodiscard]] int GetLeftBorder() const noexcept;
  [[nodiscard]] int GetRightBorder() const noexcept;

  void SetPolicy(Number number, Policy policy) noexcept;
  [[nodiscard]] Policy GetPolicy(Number number) const noexcept;

 private:
  int a_{};
  int b_{};
  int c_{};

  Policy a_policy_{Policy::RESTRICTIVE};
  Policy b_policy_{Policy::RESTRICTIVE};
  Policy c_policy_{Policy::RESTRICTIVE};

  const int left_border_{0};
  const int right_border_{100};
  const int ultimate_answer_{42};

  mutable std::shared_mutex numbers_mutex_{};

  bool UpdateA(int value, Policy policy = Policy::NONE);
  bool UpdateB(int value, Policy policy = Policy::NONE);
  bool UpdateC(int value, Policy policy = Policy::NONE);

  int Normalize(int value, int left, int right);
  };
} // namespace model
