#ifndef SESSION_H
#define SESSION_H

#include <mutex>
#include <boost/asio.hpp>

#include "Config.h"
#include "Parser.h"

namespace proxy_srv
{
class SessionManager;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(boost::asio::ip::tcp::socket socket, const Config& config, boost::asio::io_service& ioservice, SessionManager& manager);

    void Open();

private:
    void HandleUpstreamConnect(const boost::system::error_code& error);

    void HandleUpstreamRead(const boost::system::error_code& error, std::size_t size);

    void HandleDownstreamWrite(const boost::system::error_code& error);

    void HandleDownstreamRead(const boost::system::error_code& error, std::size_t size);

    void HandleUpstreamWrite(const boost::system::error_code& error);

    void Close();

    static constexpr std::size_t  BUFFER_SIZE = 8192; // 8KB
    std::array<char, BUFFER_SIZE> m_clientBuf;
    std::array<char, BUFFER_SIZE> m_remoteBuf;
    boost::asio::ip::tcp::socket  m_clientSocket;
    boost::asio::ip::tcp::socket  m_remoteSocket;
    std::mutex                    m_mutex;
    SessionManager&               m_manager;
    const Config                  m_config;
    Parser                        m_parser;
};

typedef std::shared_ptr<Session> SessionPtr;
}

#endif // SESSION_H
