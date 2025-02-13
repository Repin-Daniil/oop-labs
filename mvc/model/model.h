#pragma once

#include <observer/observer.h>
#include <shared_mutex>

namespace model {

/**
 *@brief Модель для работы с тремя целыми числами A, B, C
 *@invariant 0 <= A <= B <= C <= 100
 *@todo Должна быть сериализация! Серилизация это тоже листенер один
 */
class DeepThought : public Subject {
 public:
  enum class Number { A, B, C };
  enum class Policy { PERMISSIVE, RESTRICTIVE, FORBIDDING };

  DeepThought() = default;
  DeepThought(int a, int b, int c);

  void UpdateNumber(Number number, int value) noexcept;

  [[nodiscard]] int GetAnswerOnAnyQuestion() const noexcept;
  [[nodiscard]] int GetA() const noexcept;
  [[nodiscard]] int GetB() const noexcept;
  [[nodiscard]] int GetC() const noexcept;

  [[nodiscard]] int GetLeftBorder() const noexcept;
  [[nodiscard]] int GetRightBorder() const noexcept;


 private:
  int a_{};
  int b_{};
  int c_{};

  const int left_border_{0};
  const int right_border_{100};
  const int ultimate_answer_{42};

  mutable std::shared_mutex numbers_mutex_{};

  void UpdateA(int value, Policy policy = Policy::RESTRICTIVE);
  void UpdateB(int value, Policy policy = Policy::RESTRICTIVE);
  void UpdateC(int value, Policy policy = Policy::RESTRICTIVE);

  int Normalize(int value, int left, int right);
  };
} // namespace model
