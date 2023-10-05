#pragma once

#include "vector.h"
#include "aabb.h"
#include <vector>
#include <initializer_list>

namespace Physics::Math
{
    class Polygon
    {
    private:
        std::vector<Vector2> m_vertices;
        Vector2 m_centroid;
        Physics::Collision::Detection::Broadphase::BVH::AABB m_box;

        Vector2 find_centroid() const;
    public:
        Polygon(std::initializer_list<Vector2> vertices);

        void move(const Vector2& delta);
        void rotate(float v);
        bool is_convex() const;
        
        const std::vector<Vector2>& get_vertices() const;
        const Vector2& get_centroid() const;

        void update_AABB();
        const Physics::Collision::Detection::Broadphase::BVH::AABB& get_AABB() const;
        void set_AABB(const Physics::Collision::Detection::Broadphase::BVH::AABB& box);

        Vector2 support(Vector2 d) const;
    };
}