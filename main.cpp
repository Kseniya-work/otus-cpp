#include "lib.h"

#include <iostream>

int main(int, char **)
{
    try
    {
        auto ip_pool = write_ip_pool("ip_filter.tsv");
        make_reverse_sort(ip_pool);
        print_ip_pool(ip_pool);
        print_ip_pool(ip_pool, {0, 1});
        print_ip_pool(ip_pool, {0, 46}, {1, 70});
        print_ip_pool(ip_pool, 46);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
