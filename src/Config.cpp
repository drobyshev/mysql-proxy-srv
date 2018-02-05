#include "Config.h"

#include <iostream>

namespace proxy_srv
{
ConfigOpt ReadConfig(const std::string& localPortStr, const std::string& localAddressStr, const std::string& remotePortStr,
                     const std::string& remoteAddressStr)
try
{
    return Config
    {
        static_cast<std::uint16_t>(std::stoi(localPortStr)),
        localAddressStr,
        static_cast<std::uint16_t>(std::stoi(remotePortStr)),
        remoteAddressStr
    };
}
catch (const std::invalid_argument& ex)
{
    std::cout << "Error! " << ex.what() << std::endl;
    return ConfigOpt();
}
}
