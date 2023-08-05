#include "contact_solver.h"
#include "contact_constraint.h"

ContactConstraintSolver::ContactConstraintSolver(unsigned iterations) : m_iterations(iterations) {}

void ContactConstraintSolver::solve(std::vector<Collision>* collisions, double dt)
{
    std::vector<ContactConstraint> constraints;
    constraints.reserve(collisions->size());
    
    for (Collision& collision: *collisions) {
        constraints.emplace_back(collision);
    }

    for (unsigned i = 0; i < m_iterations; i++) {
        for (ContactConstraint& constraint : constraints) {
            constraint.solve(dt);
        }
    }
}