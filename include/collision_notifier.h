#pragma once

#include "collision_observer.h"

#include <vector>

namespace Physics
{
    class CollisionObserver;
    struct CollisionPair;

    class CollisionNotifier
    {
    private:
        std::vector<CollisionObserver*> m_observers;
    public:
        virtual ~CollisionNotifier() {};
        void attach(CollisionObserver* const observer);
        void detach(CollisionObserver* const observer);
        void notify(const CollisionPair& collision) const;
    };
}