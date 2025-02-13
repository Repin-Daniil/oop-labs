// #define CATCH_CONFIG_MAIN
// #include "catch.hpp"

#include <model.h>
#include <model.h>  // check include guards

#include <fstream>
#include <iostream>

using namespace model;

class Storage : public IListener {
 public:
  Storage(DeepThought& model) : model_(model), file_("output.txt", std::ios::trunc) {
    if (!file_) {
      throw std::runtime_error("Ошибка открытия файла!");
    }
  }

  void OnChanged() noexcept override {
    std::cout << model_.GetA() << " " << model_.GetB() << " " << model_.GetC() << std::endl;
    file_.clear();  // Сброс флагов (на всякий случай)
    file_.seekp(0); // Перемещение указателя в начало файла

    file_ << model_.GetA() << ' ' << model_.GetB() << ' ' << model_.GetC();
    file_.flush();  // Сбрасываем буфер (важно!)
  }

  ~Storage() override {
    file_.close();
  }

 private:
  DeepThought& model_;
  std::ofstream file_;
};

int main() {
  std::ifstream file("output.txt");  // Открываем файл для чтения
  if (!file) {
    std::cerr << "Ошибка открытия файла!\n";
    return 1;
  }

  int a, b, c;
  file >> a >> b >> c;  // Читаем три числа

  file.close();

  DeepThought model{a, b, c};
  model.AddObserver(std::make_shared<Storage>(model));

  while (true) {

    char letter;
    int value;
    std::cin >> letter >> value;

    switch (letter) {
      case 'A':
        model.UpdateNumber(DeepThought::Number::A, value);
        break;
      case 'B':
        model.UpdateNumber(DeepThought::Number::B, value);
        break;
      case 'C':
        model.UpdateNumber(DeepThought::Number::C, value);
        break;
    }
  }

  return EXIT_SUCCESS;
}