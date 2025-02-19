#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <tuple>

#include <model.hpp>
#include <observer/observer.hpp>

namespace mvc::utils::serialization {

class Storage : public IListener {
 public:
  explicit Storage(model::DeepThought& model, std::string_view filename);
  void OnChanged() noexcept override;

 private:
  model::DeepThought& model_;
  std::mutex mutex_;
  std::string filename_;
};

std::tuple<int, int, int> LoadNumbers(std::string_view filename);

}  // namespace mvc::utils::serialization
