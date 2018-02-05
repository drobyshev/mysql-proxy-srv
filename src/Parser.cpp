#include "Parser.h"

namespace proxy_srv
{
StringList Parser::Parse(const char* data, std::size_t size)
{
    const char BEGIN_REQUEST = 3;
    const char END_REQUEST = EOF;

    if (!data)
    {
        return StringList();
    }

    StringList requests;
    for (std::size_t i = 0; i < size; ++i)
    {
        const char ch = data[i];
        if (BEGIN_REQUEST == ch || !m_buffer.empty())
        {
            m_buffer.push_back(ch);
        }
        else if (END_REQUEST == ch)
        {
            requests.push_back(m_buffer);
            m_buffer.clear();
        }
    }
    return requests;
}
}
