#pragma once

#include "world.h"

namespace Engine
{
    class DemoWorld
    {
    public:
        virtual ~DemoWorld() = default;
        virtual Physics::World& get_world() = 0;
    };
}