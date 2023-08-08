#pragma once

class Constraint
{
protected:
    float m_total_lambda;
    float beta;
public:
    Constraint(float beta);

    virtual void solve() = 0;
};