#include "lib.h"

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


    MyContainer<int> my_container;
    for (int i = 0; i < 10; i++)
        my_container.add(i);

    std::cout << "my_container: " << std::endl;
    for (auto i : my_container)
        std::cout << i << " ";
    std::cout << std::endl;

/*
    std::map<int, int, std::less<int>, MyAllocator<std::pair<const int, int>>> my_map {{0, 1},{1, 1},{2, 1}};
    my_map.clear();
    my_map[0] = 1;
    my_map[1] = 1;
    my_map.erase(1);
    my_map[1] = 1;
    my_map[1] = 2;
*/

    // std::vector<int, MyAllocator<int>> v{1};

    return 0;
}
