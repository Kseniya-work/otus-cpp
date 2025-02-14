#pragma once

#include "logger.h"
#include <sstream>

class ConsoleLogger : public Logger
{
public:
    virtual void write(const std::ostringstream& ostream, const time_type) const override;
};
