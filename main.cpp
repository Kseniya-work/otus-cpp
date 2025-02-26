#include "include/file_logger.h"
#include "include/handler.h"
#include "include/stream_logger.h"
#include "include/vector_storage.h"

#include <iostream>
#include <memory>

int main(int argc, char *argv[]) {
    // if (argc > 1)
    {
        std::cout << argc << std::endl; //TODO delete
        std::cout << argv[0] << std::endl; //TODO delete

        // if (argv[1] < 0)
            // throw std::runtime_error("Wrong static block size.");

        using storage_type = VectorStorage;
        using handler_type = Handler<storage_type, Logger<storage_type>>;
        using logger_ptr_type = std::shared_ptr<Logger<storage_type>>;

        auto storage = std::make_shared<storage_type>();
        std::vector<logger_ptr_type> loggers = {std::make_shared<StreamLogger<storage_type>>(),
                                                std::make_shared<FileLogger<storage_type>>()};
        std::unique_ptr<handler_type> handler(new handler_type{storage, 2, loggers});

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
