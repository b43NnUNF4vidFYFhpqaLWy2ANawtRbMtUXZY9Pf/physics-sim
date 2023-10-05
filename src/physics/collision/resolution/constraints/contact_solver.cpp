#include "contact_solver.h"
#include "contact_constraint.h"
#include "rigid_body.h"

namespace Physics::Collision::Resolution::Constraints
{
    ContactConstraintSolver::ContactConstraintSolver(unsigned iterations, float beta)
        : m_iterations(iterations),
          beta(beta)
    {}

    void ContactConstraintSolver::solve(std::vector<Physics::Collision::CollisionPair>& collisions, float dt)
    {
        if (dt == 0) return;

        std::vector<ContactConstraint> constraints;
        constraints.reserve(collisions.size());
        
        for (Physics::Collision::CollisionPair& collision: collisions) {
            Physics::Dynamics::RigidBody* a = dynamic_cast<Physics::Dynamics::RigidBody*>(collision.a);
            Physics::Dynamics::RigidBody* b = dynamic_cast<Physics::Dynamics::RigidBody*>(collision.b);
            
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