#pragma once

#include "logger.h"
#include <sstream>

class ConsoleLogger : public Logger
{
public:
    void write(std::ostringstream& ostream) const override;
};
