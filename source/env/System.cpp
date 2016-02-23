#include <radix/env/System.hpp>

#include <SDL2/SDL_platform.h>

#include <radix/core/diag/AnsiConsoleLogger.hpp>
#include <radix/core/diag/StdoutLogger.hpp>

namespace radix {

std::unique_ptr<Logger> System::logger;
System::_Log System::Log;

std::random_device System::RandDev;
std::mt19937 System::Rand(System::RandDev());

void System::Init() {
  if (std::string("Linux") == SDL_GetPlatform()) {
    logger.reset(new AnsiConsoleLogger);
  } else {
    logger.reset(new StdoutLogger);
  }
}

LogInput System::_Log::operator()() {
  return LogInput(*System::logger, LogLevel::Debug);
}

LogInput System::_Log::operator()(LogLevel lvl) {
  return LogInput(*System::logger, lvl);
}

LogInput System::_Log::operator()(LogLevel lvl, const std::string &tag) {
  return LogInput(*System::logger, lvl, tag);
}

} /* namespace radix */