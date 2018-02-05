#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include "Optional.h"

namespace proxy_srv
{
struct Config
{
    std::uint16_t localPort;
    std::string   localAddress;
    std::uint16_t remotePort;
    std::string   remoteAddress;
};

using ConfigOpt = Optional<Config>;

ConfigOpt ReadConfig(const std::string& localPortStr, const std::string& localAddressStr, const std::string& remotePortStr,
                     const std::string& remoteAddressStr);
}

#endif // CONFIG_H
