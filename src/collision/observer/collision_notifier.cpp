#include "collision_notifier.h"

#include <algorithm>

namespace Physics
{
    void CollisionNotifier::attach(CollisionObserver* const observer)
    {
        m_observers.push_back(observer);
    }

    void CollisionNotifier::detach(CollisionObserver* const observer)
    {
        auto itr = std::find(m_observers.begin(), m_observers.end(), observer);
        if ( itr == m_observers.end() ) return;
        m_observers.erase(itr);
    }

    void CollisionNotifier::notify(const CollisionPair& collision) const
    {
        for (CollisionObserver* const observer : m_observers)
        {
            observer->on_collision(collision);
        }
    }
}