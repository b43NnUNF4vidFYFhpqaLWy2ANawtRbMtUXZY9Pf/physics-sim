#pragma once

class Constraint
{
protected:
    float m_total_lambda;
    float beta;
    float dt;
public:
    Constraint(float beta, float dt);

    virtual void solve() = 0;
};