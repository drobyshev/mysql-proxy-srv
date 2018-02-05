#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>

namespace proxy_srv
{
using StringList = std::vector<std::string>;

class Parser
{
public:
    StringList Parse(const char* data, std::size_t size);

private:
    std::string m_buffer;
};
}

#endif // PARSER_H
