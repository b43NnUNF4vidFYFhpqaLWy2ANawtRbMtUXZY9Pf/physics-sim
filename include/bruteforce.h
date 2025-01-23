/**
 * @file bruteforce.h
 * @author b43NnUNF4vidFYFhpqaLWy2ANawtRbMtUXZY9Pf
 * @brief The Bruteforce class implements a brute-force broadphase.
 * @version 0.1.0
 * @date 2025-01-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "collision_detector.h"

namespace Physics
{
    /**
     * @brief The Bruteforce class implements a brute-force broadphase.
     */
    class Bruteforce : public CollisionDetector
    {
    private:
        std::vector<CollisionBody*>* m_objects;
        std::vector<CollisionPair> m_collisions;
    public:
        void set_objects(std::vector<CollisionBody*>* objects) override;

        /**
         * @note Does nothing.
         * 
         */
        void update() override;
        
        /**
         * @note Does nothing.
         * 
         * @param body
         */
        void insert(CollisionBody* body) override;
        
        /**
         * @note Does nothing.
         * 
         * @param body
         */
        void remove(CollisionBody* body) override;

        /**
         * @brief Get the collisions
         * 
         * @return The collisions
         * 
         * @note Time complexity is \f$\theta(n^2)\f$ where \f$n\f$ is the number of objects.
         */
        std::vector<CollisionPair>& get_collisions() override;
    };
}
