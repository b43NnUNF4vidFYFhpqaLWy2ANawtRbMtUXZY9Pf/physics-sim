/**
 * @file collision_notifier.h
 * @author b43NnUNF4vidFYFhpqaLWy2ANawtRbMtUXZY9Pf
 * @brief The CollisionNotifier class is responsible for managing collision observers.
 * @version 0.1.0
 * @date 2025-01-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "collision_observer.h"

#include <vector>

namespace Physics
{
    class CollisionObserver;
    struct CollisionPair;

    /**
     * @brief The CollisionNotifier class notifies its observers of collisions.
     * 
     */
    class CollisionNotifier
    {
    private:
        std::vector<CollisionObserver*> m_observers;
    public:
        virtual ~CollisionNotifier() {};

        /**
         * @brief Attach an observer
         * 
         * @param observer
         */
        void attach(CollisionObserver* const observer);

        /**
         * @brief Detach an observer
         * 
         * @param observer
         */
        void detach(CollisionObserver* const observer);

        /**
         * @brief Notify observers of a collision
         * 
         * @param collision
         */
        void notify(const CollisionPair& collision) const;
    };
}