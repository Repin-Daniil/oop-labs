#include "circle.hpp"

#include <cmath>
#include <log.hpp>

namespace {
std::atomic id_counter = 0;
}

namespace circles::model {
Circle::Circle(Point center, int radius) : center_(center), radius_(radius) {
  LOG_INFO() << "Create Circle with id" << (id_.has_value() ? std::to_string(*id_) : "None") << " with center " << center_ << " and radius = " << radius_;
}

Circle::Circle(CircleID id, Point center, int radius) : id_(id), radius_(radius) {
}

CircleID Circle::Init() {
  id_ = id_counter++;

  return *id_;
}

void Circle::Select() {
  LOG_DEBUG() << "Select Circle №" << (id_.has_value() ? std::to_string(*id_) : "None");
  is_selected_ = true;
}

void Circle::Unselect() {
  LOG_DEBUG() << "Unselect Circle №" << (id_.has_value() ? std::to_string(*id_) : "None");
  is_selected_ = false;
}

void Circle::Move(Point new_center) {
  LOG_DEBUG() << "Circle №" << (id_.has_value() ? std::to_string(*id_) : "None") << " center moved to " << new_center;
  center_ = new_center;
}

void Circle::Move(int shift_x, int shift_y) {
  center_.x += shift_x;
  center_.y += shift_y;

  LOG_DEBUG() << "Circle №" << (id_.has_value() ? std::to_string(*id_) : "None") << " center moved to " << center_;
}

Point Circle::GetCenter() const noexcept {
  return center_;
}

std::tuple<Point, int> Circle::GetView() const noexcept {
  return {center_, radius_};
}

bool Circle::Shoot(Point target) const noexcept {
  return std::hypot(target.x - center_.x, target.y - center_.y) <= radius_;
}

int Circle::GetRadius() const noexcept {
  return radius_;
}

std::optional<CircleID> Circle::GetID() const noexcept {
  return id_;
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
  return os << "(" << point.x << ", " << point.y << ")";
}

}  // namespace circles::model