#pragma once

#include "logger.h"
#include <sstream>

class FileLogger : public Logger
{
public:
    void write(std::ostringstream&) const override;
};
