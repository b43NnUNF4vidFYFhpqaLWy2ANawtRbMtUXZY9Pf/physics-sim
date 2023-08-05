#pragma once

class Constraint
{
protected:
    float m_total_lambda;
public:
    Constraint();

    virtual void solve(double dt) = 0;
};