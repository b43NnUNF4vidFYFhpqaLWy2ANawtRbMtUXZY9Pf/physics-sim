#pragma once

#include "contact.h"
#include "simplex.h"

namespace Physics
{
    Contact EPA(Simplex2& simplex, const Polygon* const a, const Polygon* const b);
}