#pragma once

template <typename Storage>
class Logger
{
public:
    virtual ~Logger() = default;

    virtual void write(const Storage& storage) const = 0;
};
