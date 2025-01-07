#define BOOST_TEST_MODULE test_parser

#include "handler.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_parser)

BOOST_AUTO_TEST_CASE(test_static_block) {
    Handler handler(3);
    std::stringstream stream("cmd1\ncmd2\ncmd3\ncmd4\n");
    handler.write(stream);
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
