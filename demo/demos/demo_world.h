#pragma once

#include "world.h"

namespace Engine
{
    class DemoWorld
    {
    public:
        virtual ~DemoWorld() {};
        virtual Physics::World& get_world() = 0;
    };
}