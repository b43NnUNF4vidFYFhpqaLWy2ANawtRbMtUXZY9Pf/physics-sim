/**
 * @file collision.h
 * @author b43NnUNF4vidFYFhpqaLWy2ANawtRbMtUXZY9Pf
 * @brief The CollisionPair struct represents a pair of colliding bodies and the contact data.
 * @version 0.1.0
 * @date 2025-01-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "contact.h"

namespace Physics
{
    class CollisionBody;

    /**
     * @brief The CollisionPair struct represents a pair of colliding bodies and the contact data.
     * 
     */
    struct CollisionPair
    {
        /**
         * @brief Construct a new Collision Pair object
         * 
         * @param a 
         * @param b 
         * @param contact 
         */
        CollisionPair(CollisionBody* a, CollisionBody* b, Contact contact);

        CollisionBody* a; /**< The first body */
        CollisionBody* b; /**< The second body */
        Contact contact; /**< The contact data */
    };
}
