#include "storage.h"

namespace infrastructure {

Storage::Storage(model::DeepThought& model, std::string_view filename)
    : model_(model), file_(filename, std::ios::trunc) {
  if (!file_) {
    throw std::runtime_error("Failed to open file.");
  }
}

void Storage::OnChanged() noexcept {
  std::cout << model_.GetA() << " " << model_.GetB() << " " << model_.GetC() << std::endl;
  file_.clear();   // Сброс флагов (на всякий случай)
  file_.seekp(0);  // Перемещение указателя в начало файла

  file_ << model_.GetA() << ' ' << model_.GetB() << ' ' << model_.GetC();
  file_.flush();  // Сбрасываем буфер (важно!)
}

Storage::~Storage() {
  file_.close();
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