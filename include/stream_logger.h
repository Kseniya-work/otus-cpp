#pragma once

#include "logger.h"

#include <iostream>

template <typename Storage>
class StreamLogger : public Logger<Storage>
{
private:
    std::ostream& ostream_;

public:
    StreamLogger(std::ostream& ostream = std::cout) : ostream_(ostream) {}
    void write(const Storage& storage) const override { ostream_ << storage; }
};
