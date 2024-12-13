#include "Logger.hpp"

Logger::Logger(const std::string& file_name) {
    // Create a file sink (for logging to the file)
    std::shared_ptr<spdlog::sinks::basic_file_sink_mt> file_sink =
        std::make_shared<spdlog::sinks::basic_file_sink_mt>(file_name, true);

    // Create a console sink (for logging to stdout)
    std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> console_sink =
        std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

    // Create a vector to hold the sinks
    std::vector<std::shared_ptr<spdlog::sink>> sinks = {file_sink, console_sink};

    // Create the multi-sink logger
    logger_ = std::make_shared<spdlog::logger>(file_name, sinks.begin(), sinks.end());

    // Set the default log level (optional, default is info)
    logger_->set_level(spdlog::level::info);
}

void Logger::log(spdlog::level::level_enum level, const std::string& message) {
    // Log the message according to the specified log level
    switch (level) {
        case spdlog::level::trace:
            logger_->trace(message);
            break;
        case spdlog::level::debug:
            logger_->debug(message);
            break;
        case spdlog::level::info:
            logger_->info(message);
            break;
        case spdlog::level::warn:
            logger_->warn(message);
            break;
        case spdlog::level::err:
            logger_->error(message);
            break;
        case spdlog::level::critical:
            logger_->critical(message);
            break;
        case spdlog::level::off:
            // Do nothing if logging is turned off
            break;
    }
}

std::shared_ptr<spdlog::logger> Logger::getLogger() {
    return logger_;  // Return the logger instance if needed
}
