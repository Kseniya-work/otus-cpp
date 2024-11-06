#include "lib.h"

#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <type_traits>
#include <vector>


template <typename T>
std::enable_if_t<std::is_integral_v<T>, void> print_ip(T t)
{
    std::cout << (int)static_cast<unsigned char>(t) << std::endl;
}

template <typename T>
std::enable_if_t<std::is_same_v<std::string, T>, void> print_ip(T t)
{
    std::cout << t << std::endl;
}

/*
template<typename, typename = void>
constexpr bool is_container = false;

template<typename T>
constexpr bool is_container<
    T,
    std::void_t<decltype(std::declval<T>().emplace_back())
    >
> = true;
*/

template <typename T>
struct is_container: std::false_type {};

// partial specializations for vector
template <typename T, typename Alloc>
struct is_container<std::vector<T, Alloc>>: std::true_type {};

// partial specializations for list
template <typename T, typename Alloc>
struct is_container<std::list<T, Alloc>>: std::true_type {};

template <typename T>
std::enable_if_t<is_container<T>::value, void> print_ip(T t)
{
    if (!t.empty())
    {
        std::for_each(t.begin(), std::prev(t.end()), [](const auto i){ std::cout << i << "."; });
        std::cout << t.back() << std::endl;
    }
}


int main(int, char **) {

    print_ip( int8_t{-1} ); // 255
    print_ip( int16_t{0} ); // 0.0
    print_ip( int32_t{2130706433} ); // 127.0.0.1
    print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
    print_ip( std::string{"Hello, World!"} ); // Hello, World!
    print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
    print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100
    print_ip( std::list<short>{} ); // 400.300.200.100

    return 0;
}
