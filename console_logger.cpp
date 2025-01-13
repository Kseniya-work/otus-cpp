#include "console_logger.h"
#include <iostream>

void ConsoleLogger::write(std::ostringstream& ostream) const
{
    std::cout << ostream.str();
}
