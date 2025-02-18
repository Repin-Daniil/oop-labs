#include "form.hpp"

namespace mvc::gui {

Form::Form(int argc, char** argv, model::DeepThought& model, app::Runners& runners) :model_(model), runners_(runners){
}

void Form::Show() {

  //QApplication::exec() как-то так
}

void Form::OnChanged() noexcept {
  //TODO
}
}