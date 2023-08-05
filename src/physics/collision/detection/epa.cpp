#include "epa.h"
#include <limits>
#include <vector>
#include <stdlib.h>

#include <iostream>

constexpr float TOLERANCE = 0.001;

Contact EPA(Simplex2& simplex, const Polygon& a, const Polygon& b)
{
    Contact contact;
    contact.penetrationDepth = std::numeric_limits<float>::infinity();
    
    std::vector<CSOSupport> polytope = {simplex[0], simplex[1], simplex[2]};

    unsigned n_vertices;
    unsigned i, j;
    CSOSupport si, sj;
    Vector2 vertex_i, vertex_j;
    Vector2 ij;
    CSOSupport min_si, min_sj;
    Vector2 normal;
    float dist;
    unsigned splice_point = 0;
    CSOSupport support;
    float support_distance;
    bool boundary_found = false;
    Vector2 cp;
    
    while (!boundary_found) {
        n_vertices = polytope.size();

        for (i = 0; i < n_vertices; i++) {
            j = (i+1) % n_vertices;
            
            si = polytope[i];
            sj = polytope[j];
            vertex_i = si.c;
            vertex_j = sj.c;

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
                
                min_si = si;
                min_sj = sj;
            }
        }
        
        support = CSOSupport(a, b, contact.normal);
        support_distance = contact.normal.dot(support.c);
        
        if(abs(support_distance) > contact.penetrationDepth + TOLERANCE) {
            contact.penetrationDepth = std::numeric_limits<float>::infinity();
            polytope.insert(polytope.begin() + splice_point, support);
        } else {
            boundary_found = true;
        }
    }
    
    contact.tangent = {contact.normal.y, -contact.normal.x};
    
    // Generate contact points: https://stackoverflow.com/a/31780778
    cp = contact.normal*contact.penetrationDepth;
    
    // Compute barycentric coordinates: https://computergraphics.stackexchange.com/a/4634
    Vector2 ci = min_si.c;
    Vector2 cj = min_sj.c;
    float x = (cp - ci).mag()/(cj - ci).mag();
    float y = 1 - x;
    
    Vector2 Ai = min_si.a;
    Vector2 Aj = min_sj.a;
    Vector2 Bi = min_si.b;
    Vector2 Bj = min_sj.b;
    
    contact.a = x*Ai + y*Aj;
    contact.b = x*Bi + y*Bj;
    
    return contact;
}