#pragma once

namespace Physics::Collision::Resolution::Constraints
{
    class Constraint
    {
    protected:
        float beta;
    public:
        Constraint(float beta);

        virtual void solve() = 0;
    };
}