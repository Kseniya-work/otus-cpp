#include "allocator.h"
#include "container.h"

#include <iostream>
#include <map>
#include <vector>

constexpr int factorial(const int n)
{
    if (n == 0) return 1;
    return n * factorial(n - 1);
}

int main(int, char **)
{
    std::map<int, int> my_map1;
    for (std::size_t i = 0; i < 10; i++)
        my_map1[i] = factorial(i);

    std::map<int, int, std::less<int>, MyAllocator<std::pair<const int, int>, 10>> my_map2;
    for (std::size_t i = 0; i < 10; i++)
        my_map2[i] = factorial(i);

    for (auto [key, value] : my_map2)
        std::cout << key << " " << value << std::endl;
    std::cout << std::endl;


    MyContainer<int> my_container1;
    for (int i = 0; i < 10; i++)
        my_container1.add(i);

    MyContainer<int, MyAllocator<int, 10>> my_container2;
    for (int i = 0; i < 10; i++)
        my_container2.add(i);

    for (auto i : my_container2)
        std::cout << i << " ";
    std::cout << std::endl;

    return 0;
}
