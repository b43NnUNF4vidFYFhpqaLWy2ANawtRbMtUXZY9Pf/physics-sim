/**
 * @file world.h
 * @author b43NnUNF4vidFYFhpqaLWy2ANawtRbMtUXZY9Pf
 * @brief The World class is responsible for managing the physics simulation.
 * @version 0.1.0
 * @date 2025-01-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "collision.h"
#include "collision_detector.h"
#include "collision_solver.h"
#include <cstddef>
#include <vector>

namespace Physics
{
    /**
     * @brief The World class is responsible for managing the physics simulation.
     * 
     */
    class World
    {
    private:
        CollisionDetector* m_collision_detector;
        std::vector<CollisionBody*> m_objects;
        std::vector<CollisionSolver*> m_solvers;
        Vector2 m_gravity;

        void solve_collisions(float dt);
        void send_collision_callbacks(std::vector<CollisionPair>& collisions, float dt);
    public:
        /**
         * @brief Construct a new World object
         * 
         */
        World();

        /**
         * @brief Set the collision detector
         * 
         * @param collision_detector
         */
        void set_collision_detector(CollisionDetector* collision_detector);

        /**
         * @brief Get the collision detector
         * 
         * @return The collision detector
         */
        CollisionDetector* get_collision_detector() const;

        /**
         * @brief Reserve space for objects
         * 
         * Use this function to avoid reallocations.
         * 
         * @param cap New capacity
         */
        void reserve_objects(std::size_t cap);

        /**
         * @brief Add an object to the world
         * 
         * @param object
         */
        void add_object(CollisionBody* object);

        /**
         * @brief Remove an object from the world
         * 
         * @param object
         */
        void remove_object(CollisionBody* object);

        /**
         * @brief Get the objects
         * 
         * @return The objects
         */
        const std::vector<CollisionBody*>& get_objects() const;

        /**
         * @brief Reserve space for solvers
         * 
         * Use this function to avoid reallocations.
         * 
         * @param cap New capacity
         */
        void reserve_solvers(std::size_t cap);

        /**
         * @brief Add a solver to the world
         * 
         * @param solver
         */
        void add_solver(CollisionSolver* solver);
        
        /**
         * @brief Remove a solver from the world
         * 
         * @param solver
         */
        void remove_solver(CollisionSolver* solver);

        /**
         * @brief Set the gravity
         * 
         * @param gravity The gravity to apply to each objects centroid
         */
        void set_gravity(const Vector2& gravity);
        
        /**
         * @brief Step the simulation
         * 
         * @param dt Time step
         */
        void step(float dt);
    };
}
