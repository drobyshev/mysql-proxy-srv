#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>

#include "SessionManager.h"
#include "Config.h"

namespace proxy_srv
{
class Server
{
public:
    Server(const Config& config);

    void Run();

private:
    void DoAccept();

    boost::asio::io_service        m_ioservice;
    boost::asio::ip::tcp::acceptor m_acceptor;
    boost::asio::ip::tcp::socket   m_socket;
    SessionPtr                     m_session;
    const Config                   m_config;
    SessionManager                 m_manager;

};
}

#endif // SERVER_H
