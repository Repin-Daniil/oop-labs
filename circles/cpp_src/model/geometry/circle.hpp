#pragma once
#include <observer.hpp>

namespace circles::model {

struct Point {
  int x{};
  int y{};
};

std::ostream& operator<<(std::ostream& os, const Point& point);

enum class Color { GREEN, BLUE, RED };

using CircleID = uint64_t;

class Circles;

/**
 *@brief Класс круга с постояннм радиусом
 *@invariant Радиус — константа
 *@author Repin-Daniil <daniil.r4@yandex.ru>
 *@todo Может быть сделать приближения? Тогда радиус будет постоянным, но его нужно будет домножать при рисовании на
 *коэфыфицциент — но по идее это задачка формы менеджерить все это, модель не в курсе. Она возвращает предс тавление.
 *Кажется что это и SRP нарушает. Класс Circle хранит абстрактный круг в ваакуме
 *@todo надо как-то использовать тот факт, что это сабюжект,
 */
class Circle : public Subject {
 public:
  Circle() = default;
  Circle(Point center, int radius);

  void Move(Point new_center);
  void Move(int shift_x, int shift_y);

  void Select();
  void Unselect();
  bool Shoot(Point target) const noexcept;

  Point GetCenter() const noexcept;
  int GetRadius() const noexcept;
  std::optional<CircleID> GetID() const noexcept;
  std::tuple<Point, int> GetView() const noexcept;

 private:
  CircleID Init();
  Circle(CircleID id, Point center, int radius); // for serialization, private, only for friends

 private:
  Point center_{};
  const int radius_{10};

  std::optional<CircleID> id_{};
  std::atomic<bool> is_selected_{false};

 friend class Circles;
};

} // namspace circles::model

