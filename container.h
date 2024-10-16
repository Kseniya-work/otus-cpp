#pragma once

#include "allocator.h"

#include <cstddef>
#include <iterator>
#include <memory>

template<typename T, typename Alloc = std::allocator<T>>
class MyContainer
{
    struct Node
    {
        Node* next;
        T data;

        Node(Node* next_, T data_) : next(next_), data(data_){}
    };

    using NodeAlloc = typename Alloc::template rebind<Node>::other;

public:
    MyContainer()
    : head(nullptr)
    , prev(nullptr)
    , nodesCounter()
    {}

    ~MyContainer()
    {
        auto cur = head;
        while (cur != nullptr)
        {
            auto next = cur->next;
            std::allocator_traits<NodeAlloc>::deallocate(nodeAlloc, cur, 1);
            cur = next;
        }
    }

    void add(const T& item)
    {
        Node* cur = std::allocator_traits<NodeAlloc>::allocate(nodeAlloc, 1);

        if (nodesCounter == 0)
        {
            head = cur;
        }
        else
        {
            prev->next = cur;
        }

        std::allocator_traits<NodeAlloc>::construct(nodeAlloc, cur, Node(nullptr, item));
        prev = cur;
        nodesCounter++;
    }

struct Iterator
{
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = Node;
    using pointer           = value_type*;
    using reference         = T&;

    Iterator(pointer ptr_) : ptr(ptr_) {}

    reference operator*() const { return ptr->data; }
    pointer operator->() { return ptr; }

    // Prefix increment
    Iterator& operator++() { ptr = ptr->next; return *this; }

    // Postfix increment
    Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

    friend bool operator== (const Iterator& a, const Iterator& b) { return a.ptr == b.ptr; };
    friend bool operator!= (const Iterator& a, const Iterator& b) { return a.ptr != b.ptr; };

private:

    pointer ptr;
};

    Iterator begin() { return Iterator(head); }
    Iterator end()   { return nullptr; }

    std::size_t size() const
    {
        return nodesCounter;
    }

    bool empty() const
    {
        return nodesCounter == 0;
    }

private:
    Node* head = nullptr;
    Node* prev = nullptr;
    std::size_t nodesCounter = 0;
    Alloc allocator;
    NodeAlloc nodeAlloc;
};