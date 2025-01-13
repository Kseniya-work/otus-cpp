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

        auto storage = std::make_unique<VectorStorage<std::string>>();

        // Handler handler(argv[1]);
        Handler handler(std::move(storage), 2);  //TODO delete
        handler.write(std::cin);
    }
    /*
    else
    {
        std::cout << "no args" << std::endl;
    }
    */

    return 0;
}
