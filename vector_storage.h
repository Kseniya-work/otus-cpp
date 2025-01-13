#pragma once

#include "storage.h"
#include <memory>
#include <vector>

template <typename T>
class VectorStorage : public Storage<std::vector<T>>
{
private:
    std::vector<T> bulk_;

public:
    void add(const T& cmd) override
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

    auto begin() -> decltype(bulk_.begin())
    {
        return bulk_.begin();
    }

    auto end() -> decltype(bulk_.end())
    {
        return bulk_.end();
    }
};
