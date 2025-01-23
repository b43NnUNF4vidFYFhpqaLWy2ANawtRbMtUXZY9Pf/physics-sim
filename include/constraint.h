/**
 * @file constraint.h
 * @author b43NnUNF4vidFYFhpqaLWy2ANawtRbMtUXZY9Pf
 * @brief The Constraint class represents a constraint
 * @version 0.1.0
 * @date 2025-01-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

namespace Physics
{
    /**
     * @brief The Constraint class represents a constraint
     * 
     */
    class Constraint
    {
    protected:
        float beta; /**< \f$\beta\f$ is the Baumgarte stabilization factor */
    public:
        /**
         * @brief Construct a new Constraint object
         * 
         * @param beta The Baumgarte stabilization factor \f$\beta\f$, typically \f$0 \leq \beta \leq 1\f$, determines the rate at which to correct the positions (a velocity constraint only ensures that the constraint is not violated further): \f$\beta = 0\f$ means no positional correction, while \f$\beta = 1\f$ means positional correction in one iteration.
         */
        Constraint(float beta);

        /**
         * @brief Resolve the constraint
         * 
         */
        virtual void solve() = 0;
    };
}