#pragma once

#include "logger.h"
#include <sstream>

class FileLogger : public Logger
{
public:
    virtual void write(const std::ostringstream& ostream, const time_type time) const override;
};
