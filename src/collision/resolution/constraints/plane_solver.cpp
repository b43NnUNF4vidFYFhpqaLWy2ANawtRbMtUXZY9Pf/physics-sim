#include "plane_solver.h"
#include "plane_constraint.h"

namespace Physics
{
    PlaneConstraintSolver::PlaneConstraintSolver(unsigned iterations, float beta)
        : m_iterations(iterations),
          beta(beta)
    {}

    void PlaneConstraintSolver::solve(std::vector<CollisionPair>& collisions, float dt)
    {
        if (dt == 0) return;

        std::vector<PlaneConstraint> constraints;
        constraints.reserve(collisions.size());
        
        for (CollisionPair& collision: collisions) {
            RigidBody* a = dynamic_cast<RigidBody*>(collision.a);
            RigidBody* b = dynamic_cast<RigidBody*>(collision.b);
            
            if (a && !b) {
                // The contact normal always points from body a to body b, but the plane normal should point from plane to rigid body
                constraints.emplace_back(a, collision.contact.a, (-1)*collision.contact.normal, (-1)*collision.contact.tangent, collision.contact.penetrationDepth, beta);
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
}
