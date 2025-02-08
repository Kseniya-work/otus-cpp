#pragma once

#include <chrono>
#include <iostream>

class Logger
{
public:
    virtual ~Logger() = default;
    virtual void write(std::ostringstream& ostream, std::chrono::time_point<std::chrono::steady_clock> time) const = 0;
};
