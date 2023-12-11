#pragma once

namespace Physics
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