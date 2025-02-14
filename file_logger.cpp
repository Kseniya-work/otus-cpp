#include "file_logger.h"
#include <fstream>

void FileLogger::write(const std::ostringstream& ostream, const time_type time) const
{
    const auto duration = time.time_since_epoch();
    const auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    const auto fileName = std::to_string(msec);
    std::ofstream out;
    out.open(fileName);
    if (out.is_open())
    {
        out << ostream.str();
    }
    out.close();
}
