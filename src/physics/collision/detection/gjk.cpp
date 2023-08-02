#include "gjk.h"

Simplex2 GJK(const Polygon& a, const Polygon& b)
{
    Vector2 support = CSO_support(a, b, {1, 0});
    Simplex2 supports;
    supports.push_front(support);
    Vector2 direction = -1*support;
    
    while (true) {
        support = CSO_support(a, b, direction);
        
        if (direction.dot(support) <= 0) {
            return supports; // Fail
        }
        
        supports.push_front(support);
        
        if (update_simplex(supports, direction)) {
            supports.set_contains_origin();
            return supports;
        }
    }
}

bool update_simplex(Simplex2& supports, Vector2& direction)
{
    switch ( supports.size() ) {
        case 2: return line_case(supports, direction);
        case 3: return triangle_case(supports, direction);
    }
    
    return false; // Error
}

bool line_case(Simplex2& supports, Vector2& direction)
{
    Vector2 a = supports[0];
    Vector2 b = supports[1];
    
    Vector2 ab = b - a;
    Vector2 ao = -1*a;
    
    if (ab.dot(ao) > 0) {
        direction = ab.cross(ao).cross(ab);
    } else {
        supports = {a};
        direction = ao;
    }
    
    return false;
}


bool triangle_case(Simplex2& supports, Vector2& direction)
{
    Vector2 a = supports[0];
    Vector2 b = supports[1];
    Vector2 c = supports[2];

    Vector2 ab = b - a;
    Vector2 ac = c - a;
    Vector2 ao = -1*a;
    Vector2 abc = ab.cross(ac);
    
    if (abc.cross(ac).dot(ao) > 0) {
        if (ac.dot(ao) > 0) {
            supports = {a, c};
            direction = ac.cross(ao).cross(ac);
        } else {
            supports = {a, b};
            return line_case(supports, direction);
        }
    } else if (ab.cross(abc).dot(ao) > 0) {
        supports = {a, b};
        return line_case(supports, direction);
    } else {
        return true;
    }
    
    return false;
}