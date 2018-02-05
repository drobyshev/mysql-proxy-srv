#include <iostream>

#include "Server.h"

int main(int argc, char* argv[])
{
    const int ARG_COUNT = 5;

    if (argc != ARG_COUNT)
    {
        std::cout << "Error! Wrong arguments count" << std::endl;
        return 0;
    }

    if (const auto config = proxy_srv::ReadConfig(argv[1], argv[2], argv[3], argv[4]))
    {
        proxy_srv::Server(config.Get()).Run();
        std::cout << "Bye" << std::endl;
        return 0;
    }

    std::cout << "Error! Invalid config." << std::endl;
    return 0;
}
