#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>
#include <string>
#include <vector>

// Logger class for handling logs with different severity levels (info, error, debug, etc.).
class Logger {
public:
    // Constructor to create a logger with a specified log file
    explicit Logger(const std::string& file_name);

    // Method to log messages with a specific severity level
    void log(spdlog::level::level_enum level, const std::string& message);

    // Method to get the logger instance (optional)
    std::shared_ptr<spdlog::logger> getLogger();

private:
    std::shared_ptr<spdlog::logger> logger_;  // The logger instance
};

#endif // LOGGER_HPP
