#define BOOST_TEST_MODULE test_parser

#include "handler.h"
#include "vector_storage.h"

#include <memory>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_parser)

BOOST_AUTO_TEST_CASE(test_static_block) {
    /*
    auto storage = std::make_unique<VectorStorage<std::string>>();
    Handler handler(std::move(storage), 3);
    std::stringstream stream("cmd1\ncmd2\ncmd3\ncmd4\n");
    handler.read(stream);
    BOOST_CHECK(true);
    */
}

BOOST_AUTO_TEST_SUITE_END()
