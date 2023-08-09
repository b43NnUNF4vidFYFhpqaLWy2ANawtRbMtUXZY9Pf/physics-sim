#include "plane_solver.h"
#include "plane_constraint.h"

PlaneConstraintSolver::PlaneConstraintSolver(unsigned iterations, float beta)
    : m_iterations(iterations),
      beta(beta)
{}

void PlaneConstraintSolver::solve(std::vector<Collision>& collisions, float dt)
{
    if (dt == 0) return;

    std::vector<PlaneConstraint> constraints;
    constraints.reserve(collisions.size());
    
    for (Collision& collision: collisions) {
        RigidBody* a = dynamic_cast<RigidBody*>(collision.a);
        RigidBody* b = dynamic_cast<RigidBody*>(collision.b);
        
        if (a && !b) {
            constraints.emplace_back(a, collision.contact.a, collision.contact.normal, collision.contact.tangent, collision.contact.penetrationDepth, beta);
        } else if (b && !a) {
            constraints.emplace_back(b, collision.contact.b, collision.contact.normal, collision.contact.tangent, collision.contact.penetrationDepth, beta);
        }
    }

    for (unsigned i = 0; i < m_iterations; i++) {
        for (PlaneConstraint& constraint : constraints) {
            constraint.solve();
        }
    }
}