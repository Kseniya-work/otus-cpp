#include "console_logger.h"
#include <iostream>

void ConsoleLogger::write(std::ostringstream& ostream, std::chrono::time_point<std::chrono::steady_clock>) const
{
    std::cout << ostream.str();
}
