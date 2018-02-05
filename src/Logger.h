#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <mutex>

namespace proxy_srv
{
class Logger
{
public:
    static Logger& GetInstance();

    void Print(const std::string& msg);

private:
    Logger() {}
    Logger(const Logger& logger) = delete;
    Logger& operator=(const Logger& logger) = delete;

    std::ofstream m_logFile;
    std::mutex    m_mutex;
};

void LogPrint(const std::string& msg);
}

#endif // LOGGER_H
