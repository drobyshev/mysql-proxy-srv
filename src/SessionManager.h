#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

#include <set>
#include "Session.h"

namespace proxy_srv
{
class SessionManager
{
public:
    void Add(const SessionPtr& session);

    void Remove(const SessionPtr& session);

private:
    std::set<SessionPtr> m_sessions;
};
}

#endif // SESSION_MANAGER_H
