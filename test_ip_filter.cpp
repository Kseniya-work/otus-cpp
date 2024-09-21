#define BOOST_TEST_MODULE test_ip_filter

#include "lib.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_version)

BOOST_AUTO_TEST_CASE(test_valid_version) {
    BOOST_CHECK(version() > 0);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_ip_filter_tool)

BOOST_AUTO_TEST_CASE(parsing) {
    std::stringstream ip_pool("0.0.0\n");
    BOOST_CHECK_THROW(write_ip_pool(ip_pool), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(sorting) {
    std::stringstream stream("0.2.0.0\n0.10.0.0\n");
    auto ip_pool = write_ip_pool(stream);
    make_reverse_sort(ip_pool);
    stream.clear();
    print_ip_pool(stream, ip_pool);
    BOOST_CHECK_EQUAL(stream.str(), "0.10.0.0\n0.2.0.0\n");
}

BOOST_AUTO_TEST_SUITE_END()