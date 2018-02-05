#include "Server.h"

#include <iostream>

namespace proxy_srv
{
Server::Server(const Config& config)
    : m_acceptor(m_ioservice, boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4::from_string(config.localAddress), config.localPort))
    , m_socket(m_ioservice)
    , m_config(config)
{}

void Server::Run()
{
    DoAccept();
    m_ioservice.run();
}

void Server::DoAccept()
{
    m_acceptor.async_accept(m_socket, [this](const auto& err)
    {
        if (!m_acceptor.is_open())
        {
            return;
        }
        if (!err)
        {
            m_manager.Add(std::make_shared<Session>(std::move(m_socket), m_config, m_ioservice, m_manager));
        }
        DoAccept();
    });
}
}
