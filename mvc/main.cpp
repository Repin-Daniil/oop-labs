// #define CATCH_CONFIG_MAIN
// #include "catch.hpp"

#include <model.h>
#include <model.h>  // check include guards

#include <fstream>
#include <iostream>

#include "infrastructure/storage/storage.h"

using namespace model;


int main() {
  std::string filename = "output.txt";
  auto [a, b, c] = infrastructure::LoadNumbers(filename);

  DeepThought model{a, b, c};
  std::shared_ptr<IListener> storage = std::make_shared<infrastructure::Storage>(model, filename);

  model.AddObserver(storage.get());
  model.SetPolicy(DeepThought::Number::B, DeepThought::Policy::FORBIDDING);

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