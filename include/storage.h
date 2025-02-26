#pragma once

#include <chrono>
#include <iostream>

template <typename ContainerType>
class Storage
{
public:
    using const_iterator = typename ContainerType::const_iterator;
    using T = typename ContainerType::value_type;
    using time_type = std::chrono::time_point<std::chrono::steady_clock>;

    time_type timeStart_;

public:
    virtual ~Storage() = default;
    void setTime(const time_type t) { timeStart_ = t; }
    time_type getTime() const { return timeStart_; }

    virtual void add(const T& value) = 0;
    virtual void clear() = 0;
    virtual bool empty() const = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Storage<ContainerType>& storage)
    {
        if (!storage.empty())
        {
            os << "bulk: ";
            for (auto it = storage.cbegin(); it != storage.cend(); ++it)
                os << (it != storage.cbegin() ? ", " : "") << *it;
            os << std::endl;
        }

        return os;
    }
};