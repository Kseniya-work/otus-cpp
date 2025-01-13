#pragma once

template <typename ContainerType>
class Storage
{
public:
    using iterator = typename ContainerType::iterator;
    using T = typename ContainerType::value_type;

    virtual ~Storage() = default;
    virtual void add(const T& value) = 0;
    virtual void clear() = 0;
    virtual bool empty() const = 0;
    virtual iterator begin() = 0;
    virtual iterator end() = 0;
};
