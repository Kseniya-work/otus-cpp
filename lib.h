/*!
\file
\brief IP address print function.

The function is implemented for various input parameters by using
SFINAE mechanism.
*/

#pragma once

#include <algorithm>
#include <bit>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <list>
#include <string>
#include <type_traits>
#include <tuple>
#include <vector>

/*!
Prints the current build number
\return The current build number
*/
int version();

/*!
Prints the address bytewise in unsigned form, starting with the most highest byte,
with the symbol . (dot character) as a separator. All bytes of the number are output.
\param Address as an arbitrary integer type
*/
template <typename T>
constexpr std::enable_if_t<std::is_integral_v<T>, void> print_ip(const T & t)
{
    constexpr bool is_endian_big = std::endian::native == std::endian::big;
    int endian_depend_idx = 0;
    if constexpr (std::endian::native == std::endian::big)
        endian_depend_idx = 0;
    else if constexpr (std::endian::native == std::endian::little)
        endian_depend_idx = sizeof(T) - 1;

    const std::byte * bytes = (const std::byte *) (&t);
    for (int i = 0; i < (int)sizeof(T); i++)
        std::cout << ((is_endian_big && i != 0) || (!is_endian_big && (endian_depend_idx - i != sizeof(T) - 1)) ? "." : "") <<
                     std::to_integer<int>(bytes[std::abs(endian_depend_idx - i)]);
    std::cout << std::endl;
}

/*!
Prints as is, regardless of the content.
\param Address as a string
*/
template <typename T>
constexpr std::enable_if_t<std::is_same_v<std::string, T>, void> print_ip(const T & t)
{
    std::cout << t << std::endl;
}

template <typename T>
struct is_container: std::false_type {};

// partial specializations for vector
template <typename T, typename Alloc>
struct is_container<std::vector<T, Alloc>>: std::true_type {};

// partial specializations for list
template <typename T, typename Alloc>
struct is_container<std::list<T, Alloc>>: std::true_type {};

/*!
Prints the full contents of the container element by element and splits it. (symbol
dot). The elements are displayed as is.
\param Address in the form of containers std::list, std::vector
*/
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

/*!
Prints the address as a std::tuple, provided all types are the same.
The complete contents are output element by element and separated. (one dot symbol).
The elements are displayed as is.
\warning If the tuple types are not the same, a compilation error will be thrown.
\param Address as std::tuple
*/
template <class T>
constexpr std::enable_if_t<is_tuple<T>::value, void> print_ip(const T & t)
{
    const auto size = std::tuple_size<std::remove_reference_t<T>>::value;
    print_ip_from_tuple(t, std::make_index_sequence<size>{});
    std::cout << std::endl;
}
