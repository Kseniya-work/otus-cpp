#pragma once

#include <iostream>

class Logger
{
public:
    virtual ~Logger() = default;
    virtual void write(std::ostringstream& ostream) const = 0;
};
