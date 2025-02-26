#pragma once

#include "storage.h"
#include <vector>

class VectorStorage : public Storage<std::vector<std::string>>
{
private:
    std::vector<std::string> bulk_;

public:
    using const_iterator = std::vector<std::string>::const_iterator;

    void add(const std::string& cmd) override
    {
        bulk_.emplace_back(cmd);
    }

    void clear() override
    {
        bulk_.clear();
    }

    bool empty() const override
    {
        return bulk_.empty();
    }

    const_iterator cbegin() const override
    {
        return bulk_.cbegin();
    }

    const_iterator cend() const override
    {
        return bulk_.cend();
    }
};
