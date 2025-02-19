#include "runners.hpp"

namespace mvc::app {

Runners::Runners(model::DeepThought& model) : model_(model) {
}

void Runners::StartRunner(model::DeepThought::Number number) {
  if (!runners_.contains(number)) {
    runners_.insert({number, Runner{model_, number}});
    runners_.at(number).Start();
  }
}

void Runners::StopRunner(model::DeepThought::Number number) {
  runners_.erase(number);
}

}  // namespace mvc::app