#include "Logger.h"

#include <chrono>
#include <iomanip>

namespace
{
std::string GetFileName()
{
    const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::stringstream ss;
    ss << "proxysrv" << std::put_time(std::localtime(&now), "%FT%T");
    return ss.str();
}
}

namespace proxy_srv
{
Logger& Logger::GetInstance()
{
    static Logger logger;
    return logger;
}

void Logger::Print(const std::string& msg)
{
    const std::streamoff FILE_SIZE_MAX = 10485760; // 10MB
    const std::lock_guard<std::mutex> locker(m_mutex);
    if (!m_logFile.is_open())
    {
        m_logFile.open(GetFileName());
    }
    else if (m_logFile.tellp() + static_cast<std::streamoff>(msg.length()) >= FILE_SIZE_MAX)
    {
        m_logFile.close();
        m_logFile.open(GetFileName());
    }
    m_logFile << msg << std::endl << std::flush;
}

void LogPrint(const std::string& msg)
{
    Logger::GetInstance().Print(msg);
}
}
