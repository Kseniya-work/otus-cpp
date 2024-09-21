#include "lib.h"
#include "version.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>

int version()
{
    return PROJECT_VERSION_PATCH;
}

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
static std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    auto stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

ip_pool_type write_ip_pool(const std::string & filename)
{
    ip_pool_type ip_pool;
    std::ifstream in(filename);
    if (in.is_open())
    {
        for(std::string line; std::getline(in, line);)
        {
            const auto ip_str = split(split(line, '\t').at(0), '.');
            if (ip_str.size() != 4) throw std::runtime_error("Wrong ip length.");

            ip_type ip(4);
            for (std::size_t i = 0; i < 4; i++)
            {
                const int ip_part = std::stoi(ip_str[i]);
                if (ip_part < 0 || ip_part > 255)
                    throw std::out_of_range("Value is out of range for unsigned char.");
                ip[i] = static_cast<unsigned char>(ip_part);
            }
            ip_pool.emplace_back(std::move(ip));
        }
    }
    else
    {
        std::cout << "The input file cannot be opened." << std::endl;
    }
    in.close();
    return ip_pool;
}

void make_reverse_sort(ip_pool_type & ip_pool)
{
    std::sort(ip_pool.begin(), ip_pool.end(), [](const auto & ip1, const auto & ip2)
        {
            auto it_pair = std::mismatch(ip1.cbegin(), ip1.cend(), ip2.cbegin(), ip2.cend());
            return *it_pair.first > *it_pair.second;
        }
    );
}

static auto print_ip = [](const auto & ip)
{
    std::cout << static_cast<int>(ip.at(0)) << "." <<
                 static_cast<int>(ip.at(1)) << "." <<
                 static_cast<int>(ip.at(2)) << "." <<
                 static_cast<int>(ip.at(3)) << std::endl;
};

void print_ip_pool(const ip_pool_type & ip_pool)
{
    std::for_each(ip_pool.cbegin(), ip_pool.cend(), print_ip);
}

void print_ip_pool(const ip_pool_type & ip_pool,
                   const std::pair<std::size_t, int> & byte)
{
    std::for_each(ip_pool.cbegin(), ip_pool.cend(),
        [&](const auto & ip){ if (ip.at(byte.first) == byte.second) print_ip(ip); });
}

void print_ip_pool(const ip_pool_type & ip_pool,
                   const std::pair<std::size_t, int> & byte1,
                   const std::pair<std::size_t, int> & byte2)
{
    std::for_each(ip_pool.cbegin(), ip_pool.cend(),
        [&](const auto & ip){ if ((ip.at(byte1.first) == byte1.second) &&
                                  (ip.at(byte2.first) == byte2.second)) print_ip(ip); });
}

void print_ip_pool(const ip_pool_type & ip_pool, const int value)
{
    std::for_each(ip_pool.cbegin(), ip_pool.cend(),
        [&](const auto & ip){ if (std::any_of(ip.cbegin(), ip.cend(),
            [&](const auto & b){ return b == value; })) print_ip(ip); });
}
