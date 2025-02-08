#pragma once

#include "logger.h"
#include <sstream>

class FileLogger : public Logger
{
public:
    virtual void write(std::ostringstream& ostream, std::chrono::time_point<std::chrono::steady_clock> time) const override;
};
