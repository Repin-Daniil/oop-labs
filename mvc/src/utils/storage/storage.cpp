#include "storage.hpp"

#include <tuple>

#include <log.hpp>

namespace mvc::utils::serialization {

Storage::Storage(model::DeepThought& model, std::string_view filename) : model_(model), filename_(filename) {
}

void Storage::OnChanged() noexcept {
  std::lock_guard lock(mutex_);
  std::ofstream file(filename_, std::ios::trunc);

  if (!file) {
    return;
  }

  file << model_.GetA() << ' ' << model_.GetB() << ' ' << model_.GetC();
  file.flush();
}

std::tuple<int, int, int> LoadNumbers(std::string_view filename) {
  std::ifstream file(filename);
  if (!file) {
    LOG_ERROR() << "Файл не найден";
    return {};
  }

  int a, b, c;
  file >> a >> b >> c;

  file.close();
  return {a, b, c};
}

}  // namespace mvc::utils::serialization
