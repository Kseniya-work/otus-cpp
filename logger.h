#pragma once

#include <chrono>
#include <iostream>

class Logger
{
public:
    using time_type = std::chrono::time_point<std::chrono::steady_clock>;
    virtual ~Logger() = default;
    virtual void write(const std::ostringstream& ostream, const time_type time) const = 0;
};
