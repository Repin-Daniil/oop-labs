#include "circles.hpp"

#include <ranges>

namespace circles::model {

CircleID Circles::AddCircle(const std::shared_ptr<Circle>& new_circle) {
  auto id = new_circle->Init();

  circles_map_.insert({id, new_circle});
  circles_.push_back(new_circle);

  return id;
}

void Circles::DeleteCircle(CircleID circle_id) {
  if (circles_map_.contains(circle_id)) {
    circles_map_.erase(circle_id);
  }
}

void Circles::Shoot(Point target) {
  std::vector<std::shared_ptr<Circle>> shooted_circles;  // FIXME Switch to my container

  for (auto& [id, circle] : circles_map_) {
    if (circle->Shoot(target)) {
      shooted_circles.push_back(circle);
    }
  }

  std::ranges::sort(shooted_circles, [](const std::shared_ptr<Circle>& lhs, const std::shared_ptr<Circle>& rhs) {
    return lhs->id_ < rhs->id_;
  });

  if (select_policy_ == SelectPolicy::kChooseAll) {
    for (auto& circle : shooted_circles) {
      circle->Select();
    }
  } else {
    std::ranges::sort(shooted_circles, [](const std::shared_ptr<Circle>& lhs, const std::shared_ptr<Circle>& rhs) {
      return lhs->id_ < rhs->id_;
    });

    auto circle = (select_policy_ == SelectPolicy::kChooseFirst ? shooted_circles.front() : shooted_circles.back());
    circle->Select();
  }
}

void Circles::SetSelectPolicy(SelectPolicy select_policy) {
  select_policy_ = select_policy;
}

Circles::SelectPolicy Circles::GetSelectPolicy() const noexcept {
  return select_policy_;
}

std::shared_ptr<Circle> Circles::GetCircle(CircleID circle_id) {
  if (circles_map_.contains(circle_id)) {
    return circles_map_.at(circle_id);
  }

  return nullptr;
}

}  // namespace circles::model
