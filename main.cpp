#include "handler.h"

#include <iostream>

int main(int argc, char *argv[]) {
    // if (argc > 1)
    {
        std::cout << argc << std::endl; //TODO delete
        std::cout << argv[0] << std::endl; //TODO delete

        // if (argv[1] < 0)
            // throw std::runtime_error("Wrong static block size.");

        // Handler handler(argv[1]);
        Handler handler(3);  //TODO delete
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
