#include "contact_solver.h"
#include "contact_constraint.h"
#include "rigid_body.h"

namespace Physics
{
    ContactConstraintSolver::ContactConstraintSolver(unsigned iterations, float beta)
        : m_iterations(iterations),
          beta(beta)
    {}

    void ContactConstraintSolver::solve(std::vector<CollisionPair>& collisions, float dt)
    {
        if (dt == 0) return;

        std::vector<ContactConstraint> constraints;
        constraints.reserve(collisions.size());
        
        for (CollisionPair& collision: collisions) {
            RigidBody* a = dynamic_cast<RigidBody*>(collision.a);
            RigidBody* b = dynamic_cast<RigidBody*>(collision.b);
            
            if (a && b) {
                constraints.emplace_back(a, b, collision.contact, beta, dt);
            }
        }

        for (unsigned i = 0; i < m_iterations; i++) {
            for (ContactConstraint& constraint : constraints) {
                constraint.solve();
            }
        }
    }
}