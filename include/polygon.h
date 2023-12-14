#pragma once

#include "vector.h"
#include "aabb.h"
#include <vector>

namespace Physics
{
    class Polygon
    {
    private:
        std::vector<Vector2> m_vertices;
        Vector2 m_centroid;
        AABB m_box;

        Vector2 find_centroid() const;
    public:
        Polygon(std::vector<Vector2> vertices);

        void move(const Vector2& delta);
        void rotate(float v);
        bool is_convex() const;
        
        const std::vector<Vector2>& get_vertices() const;
        const Vector2& get_centroid() const;

        void update_AABB();
        const AABB& get_AABB() const;
        void set_AABB(const AABB& box);

        Vector2 support(Vector2 d) const;
    };
}