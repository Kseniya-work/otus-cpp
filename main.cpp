#include "console_logger.h"
#include "file_logger.h"
#include "handler.h"
#include "vector_storage.h"

#include <iostream>
#include <memory>

int main(int argc, char *argv[]) {
    // if (argc > 1)
    {
        std::cout << argc << std::endl; //TODO delete
        std::cout << argv[0] << std::endl; //TODO delete

        // if (argv[1] < 0)
            // throw std::runtime_error("Wrong static block size.");

        using storage_type = VectorStorage<std::string>;
        using handler_type = Handler<storage_type, Logger>;

        auto storage = std::make_unique<storage_type>();
        std::vector<std::shared_ptr<Logger>> loggers = {std::make_shared<ConsoleLogger>(),
                                                        std::make_shared<FileLogger>()};
        std::unique_ptr<handler_type> handler(
            new handler_type{2, std::move(storage), loggers});

        handler->read(std::cin);
    }
    /*
    else
    {
        std::cout << "no args" << std::endl;
    }
    */

    return 0;
}
