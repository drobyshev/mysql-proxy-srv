#include "Session.h"

#include "SessionManager.h"
#include "Logger.h"

namespace proxy_srv
{
Session::Session(boost::asio::ip::tcp::socket socket, const Config& config, boost::asio::io_service& ioservice, SessionManager& manager)
    : m_clientSocket(std::move(socket))
    , m_remoteSocket(ioservice)
    , m_manager(manager)
    , m_config(config)
{}

void Session::Open()
{
    auto self(shared_from_this());
    const boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(m_config.remoteAddress), m_config.remotePort);
    m_remoteSocket.async_connect(endpoint, [this, self](const auto& err)
    {
        if (!err)
        {
            m_remoteSocket.async_read_some(boost::asio::buffer(m_remoteBuf), [this](const auto& err, auto size)
            {
                HandleRemoteRead(err, size);
            });

            m_clientSocket.async_read_some(boost::asio::buffer(m_clientBuf), [this](const auto& err, auto size)
            {
                HandleClientRead(err, size);
            });
        }
        else
        {
            Close();
        }
    });
}

void Session::HandleRemoteConnect(const boost::system::error_code& error)
{
    auto self(shared_from_this());
    if (!error)
    {
        m_remoteSocket.async_read_some(boost::asio::buffer(m_remoteBuf), [this, self](const auto& err, auto size)
        {
            HandleRemoteRead(err, size);
        });

        m_clientSocket.async_read_some(boost::asio::buffer(m_clientBuf), [this, self](const auto& err, auto size)
        {
            HandleClientRead(err, size);
        });
    }
    else
    {
        Close();
    }
}

void Session::HandleRemoteRead(const boost::system::error_code& error, std::size_t size)
{
    auto self(shared_from_this());
    if (!error)
    {
        async_write(m_clientSocket, boost::asio::buffer(m_remoteBuf.data(), size), [this, self](const auto& err, auto /*size*/)
        {
            HandleClientWrite(err);
        });
    }
    else
    {
        Close();
    }
}

void Session::HandleClientWrite(const boost::system::error_code& error)
{
    auto self(shared_from_this());
    if (!error)
    {
        m_remoteSocket.async_read_some(boost::asio::buffer(m_remoteBuf), [this, self](const auto& err, auto size)
        {
            HandleRemoteRead(err, size);
        });
    }
    else
    {
        Close();
    }
}

void Session::HandleClientRead(const boost::system::error_code& error, std::size_t size)
{
    const auto requests = m_parser.Parse(m_clientBuf.data(), size);
    std::for_each(requests.cbegin(), requests.cend(), [this](const auto& req) { LogPrint(req); });
    auto self(shared_from_this());
    if (!error)
    {
        async_write(m_remoteSocket, boost::asio::buffer(m_clientBuf.data(), size), [this, self](const auto& err, auto /*size*/)
        {
            HandleRemoteWrite(err);
        });
    }
    else
    {
        Close();
    }
}

void Session::HandleRemoteWrite(const boost::system::error_code& error)
{
    auto self(shared_from_this());
    if (!error)
    {
        m_clientSocket.async_read_some(boost::asio::buffer(m_clientBuf), [this, self](const auto& err, auto size)
        {
            HandleClientRead(err, size);
        });
    }
    else
    {
        Close();
    }
}

void Session::Close()
{
    const std::lock_guard<std::mutex> locker(m_mutex);
    if (m_clientSocket.is_open())
    {
        m_clientSocket.close();
    }
    if (m_remoteSocket.is_open())
    {
        m_remoteSocket.close();
    }
    m_manager.Remove(shared_from_this());
}
}
