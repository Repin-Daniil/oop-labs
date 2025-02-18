#include "storage.h"

namespace mvc::infrastructure {

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
    std::cout << "Файл не найден" << std::endl;
    return {};
  }

  int a, b, c;
  file >> a >> b >> c;  // Читаем три числа

  file.close();
  return {a, b, c};
}

}