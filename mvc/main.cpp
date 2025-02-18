#include <QApplication>
#include <QPushButton>

#include <model/model.h>
#include <app/application.h>
#include <infrastructure/log/log.hpp>
#include <infrastructure/storage/storage.h>

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  QPushButton button("Hello world!", nullptr);
  button.resize(200, 100);
  button.show();
  return QApplication::exec();
}


int main() {
  mvc::infrastructure::log::SetLogLevel(mvc::infrastructure::log::LogLevel::INFO);
  mvc::app::Application app{"output.txt"};


  // auto& model = app.GetModel();
  // app.StartRunner(DeepThought::Number::B);
  // std::this_thread::sleep_for(std::chrono::milliseconds(1330));
  //
  // // app.StartRunner(DeepThought::Number::A);
  // app.StartRunner(DeepThought::Number::C);




  return EXIT_SUCCESS;
}