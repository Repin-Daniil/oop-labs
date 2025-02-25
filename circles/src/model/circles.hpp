#pragma once

#include <geometry/circle.hpp>
#include <memory>
#include <unordered_map>

namespace circles::model {

class Circles : public Subject {
 public:
  enum class SelectPolicy { kChooseFirst, kChooseLast, kChooseAll };

  CircleID AddCircle(const std::shared_ptr<Circle>& new_circle);
  void DeleteCircle(CircleID circle_id);
  std::shared_ptr<Circle> GetCircle(CircleID circle_id);

  void Shoot(Point target);

  void SetSelectPolicy(SelectPolicy select_policy);
  SelectPolicy GetSelectPolicy() const noexcept;

 private:
  std::unordered_map<CircleID, std::shared_ptr<Circle>> circles_map_;

  SelectPolicy select_policy_{SelectPolicy::kChooseFirst};
};

}  // namespace circles::model