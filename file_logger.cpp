#include "file_logger.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

void FileLogger::write(std::ostringstream& ostream, std::chrono::time_point<std::chrono::steady_clock> time) const
{
    auto duration = time.time_since_epoch();
    auto sec = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(std::to_string(sec), true);
    auto logger = std::make_shared<spdlog::logger>("file_logger", file_sink);
    spdlog::register_logger(logger);
    logger->info(ostream.str());
}
