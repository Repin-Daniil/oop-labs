#include <app/application.hpp>
#include <infrastructure/log/log.hpp>

int main(int argc, char* argv[]) {
  SetLogLevel(mvc::infrastructure::log::LogLevel::INFO);

  mvc::app::Application app{"output.txt", argc, argv};
  app.Run();

  return EXIT_SUCCESS;
}