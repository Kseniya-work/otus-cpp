#pragma once

#include "logger.h"
#include <sstream>

class ConsoleLogger : public Logger
{
public:
    virtual void write(std::ostringstream& ostream, std::chrono::time_point<std::chrono::steady_clock>) const override;
};
