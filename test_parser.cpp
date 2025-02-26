#define BOOST_TEST_MODULE test_parser

#include "include/handler.h"
#include "include/stream_logger.h"
#include "include/vector_storage.h"

#include <memory>
#include <iostream>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_parser)

using storage_type = VectorStorage;
using handler_type = Handler<storage_type, Logger<storage_type>>;
using logger_ptr_type = std::shared_ptr<Logger<storage_type>>;

BOOST_AUTO_TEST_CASE(static_block) {
    auto storage = std::make_shared<storage_type>();
    std::ostringstream out;
    std::vector<logger_ptr_type> loggers = {std::make_shared<StreamLogger<storage_type>>(out)};
    std::unique_ptr<handler_type> handler(new handler_type{storage, 2, loggers});

    std::stringstream input("cmd1\ncmd2\ncmd3\nEOF\n");
    std::stringstream expected("bulk: cmd1, cmd2\nbulk: cmd3\n");
    handler->read(input);
    BOOST_CHECK_EQUAL(out.str(), expected.str());
}

BOOST_AUTO_TEST_CASE(dynamic_block) {
    auto storage = std::make_shared<storage_type>();
    std::ostringstream out;
    std::vector<logger_ptr_type> loggers = {std::make_shared<StreamLogger<storage_type>>(out)};
    std::unique_ptr<handler_type> handler(new handler_type{storage, 2, loggers});

    std::stringstream input("cmd1\n{\ncmd11\ncmd12\ncmd13\n}\nEOF\n");
    std::stringstream expected("bulk: cmd1\nbulk: cmd11, cmd12, cmd13\n");
    handler->read(input);
    BOOST_CHECK_EQUAL(out.str(), expected.str());
}

BOOST_AUTO_TEST_CASE(dynamic_block_ignore) {
    auto storage = std::make_shared<storage_type>();
    std::ostringstream out;
    std::vector<logger_ptr_type> loggers = {std::make_shared<StreamLogger<storage_type>>(out)};
    std::unique_ptr<handler_type> handler(new handler_type{storage, 2, loggers});

    std::stringstream input("cmd1\n{\ncmd11\ncmd12\ncmd13\nEOF\n");
    std::stringstream expected("bulk: cmd1\n");
    handler->read(input);
    BOOST_CHECK_EQUAL(out.str(), expected.str());
}

BOOST_AUTO_TEST_CASE(dynamic_block_symbol_ignore) {
    auto storage = std::make_shared<storage_type>();
    std::ostringstream out;
    std::vector<logger_ptr_type> loggers = {std::make_shared<StreamLogger<storage_type>>(out)};
    std::unique_ptr<handler_type> handler(new handler_type{storage, 2, loggers});

    std::stringstream input("cmd1\n}\ncmd3\nEOF\n");
    std::stringstream expected("bulk: cmd1, }\nbulk: cmd3\n");
    handler->read(input);
    BOOST_CHECK_EQUAL(out.str(), expected.str());
}

BOOST_AUTO_TEST_CASE(inner_dynamic_block) {
    auto storage = std::make_shared<storage_type>();
    std::ostringstream out;
    std::vector<logger_ptr_type> loggers = {std::make_shared<StreamLogger<storage_type>>(out)};
    std::unique_ptr<handler_type> handler(new handler_type{storage, 2, loggers});

    std::stringstream input("{\ncmd1\n{\ncmd2\ncmd3\n}\n}\nEOF\n");
    std::stringstream expected("bulk: cmd1, cmd2, cmd3\n");
    handler->read(input);
    BOOST_CHECK_EQUAL(out.str(), expected.str());
}

BOOST_AUTO_TEST_CASE(dynamic_blocks_ignore) {
    auto storage = std::make_shared<storage_type>();
    std::ostringstream out;
    std::vector<logger_ptr_type> loggers = {std::make_shared<StreamLogger<storage_type>>(out)};
    std::unique_ptr<handler_type> handler(new handler_type{storage, 2, loggers});

    std::stringstream input("{\ncmd1\n{\ncmd2\ncmd3\n}\nEOF\n");
    std::stringstream expected("");
    handler->read(input);
    BOOST_CHECK_EQUAL(out.str(), expected.str());
}

BOOST_AUTO_TEST_CASE(zero_static) {
    auto storage = std::make_shared<storage_type>();
    std::ostringstream out;
    std::vector<logger_ptr_type> loggers = {std::make_shared<StreamLogger<storage_type>>(out)};
    std::unique_ptr<handler_type> handler(new handler_type{storage, 0, loggers});

    std::stringstream input("{\ncmd1\ncmd2\ncmd3\n}\nEOF\n");
    std::stringstream expected("bulk: cmd1, cmd2, cmd3\n");
    handler->read(input);
    BOOST_CHECK_EQUAL(out.str(), expected.str());
}

BOOST_AUTO_TEST_SUITE_END()
