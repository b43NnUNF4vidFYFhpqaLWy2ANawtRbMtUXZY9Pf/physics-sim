#include "epa.h"
#include <limits>
#include <vector>
#include <stdlib.h>

constexpr float TOLERANCE = 0.001;

Contact EPA(Simplex2& simplex, const Polygon& a, const Polygon& b)
{
    Contact contact;
    contact.penetrationDepth = std::numeric_limits<float>::infinity();
    
    std::vector<Vector2> polytope = {simplex[0], simplex[1], simplex[2]};

    unsigned n_vertices;
    unsigned i, j;
    Vector2 vertex_i, vertex_j;
    Vector2 ij;
    Vector2 normal;
    float dist;
    unsigned splice_point = 0;
    Vector2 support;
    float support_distance;
    bool boundary_found = false;
    
    while (!boundary_found) {
        n_vertices = polytope.size();

        for (i = 0; i < n_vertices; i++) {
            j = (i+1) % n_vertices;
            
            vertex_i = polytope[i];
            vertex_j = polytope[j];

            ij = vertex_j - vertex_i;
            normal = Vector2(ij.y, -ij.x).norm();
            dist = normal.dot(vertex_i);
            
            if (dist < 0) {
                dist *= -1;
                normal *= -1;
            }
            
            if (dist < contact.penetrationDepth) {
                contact.penetrationDepth = dist;
                contact.normal = normal;
                splice_point = j;
            }
        }
        
        support = CSO_support(a, b, contact.normal);
        support_distance = contact.normal.dot(support);
        
        if(abs(support_distance) > contact.penetrationDepth + TOLERANCE) {
            contact.penetrationDepth = std::numeric_limits<float>::infinity();
            polytope.insert(polytope.begin() + splice_point, support);
        } else {
            boundary_found = true;
        }
    }
    
    contact.tangent = {contact.normal.y, -contact.normal.x};
    
    return contact;
}