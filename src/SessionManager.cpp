#include "SessionManager.h"

namespace proxy_srv
{
void SessionManager::Add(const SessionPtr& session)
{
    if (session)
    {
        m_sessions.insert(session);
    }
}

void SessionManager::Remove(const SessionPtr& session)
{
    if (session)
    {
        m_sessions.erase(session);
    }
}
}
