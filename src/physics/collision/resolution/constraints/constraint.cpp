#include "constraint.h"

Constraint::Constraint(float beta, float dt)
    : m_total_lambda(0),
      beta(beta),
      dt(dt)
{}