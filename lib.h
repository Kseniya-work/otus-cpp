#pragma once

#include <string>
#include <vector>

using ip_type = std::vector<unsigned char>;
using ip_pool_type = std::vector<ip_type>;

int version();

// write ip pool from file
ip_pool_type write_ip_pool(const std::string & filename);

// reverse lexicographically sort
void make_reverse_sort(ip_pool_type & ip_pool);

void print_ip_pool(const ip_pool_type &);
void print_ip_pool(const ip_pool_type &, const std::pair<std::size_t, int> &);
void print_ip_pool(const ip_pool_type &, const std::pair<std::size_t, int> &, const std::pair<std::size_t, int> &);
void print_ip_pool(const ip_pool_type &, const int);
