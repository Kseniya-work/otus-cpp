#pragma once

#include <cstddef>  // For std::ptrdiff_t
#include <iostream>
#include <iterator> // For std::forward_iterator_tag
#include <memory>

struct deleter
{
    void operator()(void* ptr)
    {
        #ifndef NDEBUG
            std::cout << "deleter" << std::endl;
        #endif

        ::operator delete(ptr);
    }
};

template <class T, std::size_t Capacity = 10>
struct MyAllocator
{
    using value_type = T;

    std::shared_ptr<void> pool;
    std::size_t fillSize = 0;

    MyAllocator() noexcept
    : pool(::operator new(Capacity * sizeof(T)), deleter())
    , fillSize(0)
    {}

    template <class U, std::size_t CapacityOther>
    MyAllocator(const MyAllocator <U, CapacityOther>& a) noexcept
    : MyAllocator()
    {
        if (Capacity == CapacityOther)
            pool = a.pool;
    }

    [[nodiscard]] T* allocate(std::size_t n)
    {
        if ((n != 1) || (fillSize + n > Capacity))
            throw std::bad_alloc();

        if (auto p = reinterpret_cast<T*>(reinterpret_cast<uint8_t *>(pool.get()) + fillSize * sizeof(T)))
        {
            #ifndef NDEBUG
                report(p, n);
            #endif

            fillSize += n;
            return p;
        }

        throw std::bad_alloc();
    }

    void deallocate(T* p, std::size_t n)
    {
        // dummy implementation
        #ifndef NDEBUG
            report(p, n, 0);
        #endif

        if (p == nullptr)
            throw std::invalid_argument("Can't deallocate a null pointer");

        if (fillSize < n)
            throw std::runtime_error("Can't deallocate already deallocated memory");

        fillSize -= n;
    }

    MyAllocator select_on_container_copy_construction() const
    {
        return MyAllocator();
    }

    template <class U>
    struct rebind
    {
        typedef MyAllocator<U, Capacity> other;
    };

    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type;

private:

    void report(T* p, std::size_t n, bool alloc = true) const
    {
        std::cout << (alloc ? "Alloc: " : "Dealloc: ") << sizeof(T) * n
                  << " bytes at " << std::hex << std::showbase
                  << reinterpret_cast<void*>(p) << std::dec << '\n';
    }
};

template <class T, std::size_t Capacity1, class U, std::size_t Capacity2>
bool operator==(const MyAllocator <T, Capacity1>& a1, const MyAllocator <U, Capacity2>& a2)
{
    return (a1.pool == a2.pool) && (Capacity1 == Capacity2);
}

template <class T, std::size_t Capacity1, class U, std::size_t Capacity2>
bool operator!=(const MyAllocator <T, Capacity1>& a1, const MyAllocator <U, Capacity2>& a2)
{
    return (a1.pool != a2.pool) || (Capacity1 != Capacity2);
}


template<typename T, typename Alloc = std::allocator<T>>
class MyContainer
{
    struct Node
    {
        Node* next;
        T data;

        Node(Node* next_, T data_) : next(next_), data(data_){}
    };

    typename Alloc::template rebind<Node>::other nodeAlloc;

public:
    MyContainer()
    : head(nullptr)
    , prev(nullptr)
    , nodesCounter()
    {}

    void add(const T& item)
    {
        Node* cur = nodeAlloc.allocate(1);

        if (nodesCounter == 0)
        {
            head = cur;
        }
        else
        {
            prev->next = cur;
        }

        nodeAlloc.construct(cur, Node(nullptr, item));
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
};