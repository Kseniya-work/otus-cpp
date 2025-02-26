#pragma once

#include "logger.h"

#include <chrono>
#include <fstream>

template <typename Storage>
class FileLogger : public Logger<Storage>
{
public:
    using time_type = std::chrono::time_point<std::chrono::steady_clock>;

    void write(const Storage& storage) const override
    {
        std::ofstream out(getFileName(storage.getTime()));
        if (out.is_open())
            out << storage;
        out.close();
    }

private:
    std::string getFileName(const time_type time) const
    {
        const auto duration = time.time_since_epoch();
        const auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        return std::to_string(msec);
    }
};
