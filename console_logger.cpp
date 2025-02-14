#include "console_logger.h"
#include <iostream>

void ConsoleLogger::write(const std::ostringstream& ostream, const time_type) const
{
    std::cout << ostream.str();
}
