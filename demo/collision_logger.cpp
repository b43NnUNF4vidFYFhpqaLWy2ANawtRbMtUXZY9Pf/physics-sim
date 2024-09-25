#include "collision_logger.h"

#include <iostream>

namespace Engine
{
    void CollisionLogger::on_collision(const Physics::CollisionPair& collision)
    {
        std::cout << "Collision detected between " << collision.a << " and " << collision.b << std::endl;
    }
}