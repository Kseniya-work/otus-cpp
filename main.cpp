#include "lib.h"

#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <type_traits>
#include <tuple>
#include <vector>


template <typename T>
constexpr std::enable_if_t<std::is_integral_v<T>, void> print_ip(const T & t)
{
    std::cout << (int)static_cast<unsigned char>(t) << std::endl;
}

template <typename T>
constexpr std::enable_if_t<std::is_same_v<std::string, T>, void> print_ip(const T & t)
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
constexpr std::enable_if_t<is_container<T>::value, void> print_ip(const T & t)
{
    if (!t.empty())
    {
        std::for_each(t.begin(), std::prev(t.end()), [](const auto i){ std::cout << i << "."; });
        std::cout << t.back() << std::endl;
    }
}


template <typename... T>
struct is_tuple: std::false_type {};

// partial specializations for tuple
template<typename T, typename... U>
struct is_tuple<std::tuple<T, U...>>: std::true_type
{
    static constexpr std::enable_if_t<((std::is_same_v<T, U>) && ...), bool> areSimilarArgs = true;
};

template <class T, std::size_t... I>
constexpr void print_ip_from_tuple(const T & t, std::index_sequence<I...>)
{
    ((std::cout << (I ? "." : "") << std::get<I>(t)), ...);
}

template <class T>
constexpr std::enable_if_t<is_tuple<T>::value, void> print_ip(const T & t)
{
    const auto size = std::tuple_size<std::remove_reference_t<T>>::value;
    print_ip_from_tuple(t, std::make_index_sequence<size>{});
    std::cout << std::endl;
}


int main(int, char **) {
    print_ip( int8_t{-1} ); // 255
    print_ip( int16_t{0} ); // 0.0
    print_ip( int32_t{2130706433} ); // 127.0.0.1
    print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
    print_ip( std::string{"Hello, World!"} ); // Hello, World!
    print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
    print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100
    print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0
    // print_ip( std::make_tuple(123, 456, 789, "dd") ); // compile time error

    return 0;
}
