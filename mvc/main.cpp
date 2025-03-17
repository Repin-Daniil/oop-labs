#include <app/application.hpp>
#include <log.hpp>

int main(int argc, char* argv[]) {
  SetLogLevel(mvc::utils::log::LogLevel::INFO);

  mvc::app::Application app{"output.txt", argc, argv};
  app.Run();

  return EXIT_SUCCESS;
}