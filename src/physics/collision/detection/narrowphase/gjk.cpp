#include "gjk.h"

namespace Physics::Collision::Detection::Narrowphase
{
    Simplex2 GJK(const Physics::Math::Polygon& a, const Physics::Math::Polygon& b)
    {
        CSOSupport support(a, b, {1, 0});
        Simplex2 supports;
        supports.push_front(support);
        Physics::Math::Vector2 direction = -1*support.c;
        
        while (true) {
            support = CSOSupport(a, b, direction);
            
            if (direction.dot(support.c) <= 0) {
                return supports; // Fail
            }
            
            supports.push_front(support);
            
            if (update_simplex(supports, direction)) {
                supports.set_contains_origin();
                return supports;
            }
        }
    }

    bool update_simplex(Simplex2& supports, Physics::Math::Vector2& direction)
    {
        switch ( supports.size() ) {
            case 2: return line_case(supports, direction);
            case 3: return triangle_case(supports, direction);
        }
        
        return false; // Error
    }

    bool line_case(Simplex2& supports, Physics::Math::Vector2& direction)
    {

        CSOSupport A = supports[0];
        CSOSupport B = supports[1];

        Physics::Math::Vector2 a = A.c;
        Physics::Math::Vector2 b = B.c;
        
        Physics::Math::Vector2 ab = b - a;
        Physics::Math::Vector2 ao = -1*a;
        
        if (ab.dot(ao) > 0) {
            direction = ab.cross(ao).cross(ab);
        } else {
            supports = {A};
            direction = ao;
        }
        
        return false;
    }


    bool triangle_case(Simplex2& supports, Physics::Math::Vector2& direction)
    {
        CSOSupport A = supports[0];
        CSOSupport B = supports[1];
        CSOSupport C = supports[2];

        Physics::Math::Vector2 a = A.c;
        Physics::Math::Vector2 b = B.c;
        Physics::Math::Vector2 c = C.c;

        Physics::Math::Vector2 ab = b - a;
        Physics::Math::Vector2 ac = c - a;
        Physics::Math::Vector2 ao = -1*a;
        Physics::Math::Vector2 abc = ab.cross(ac);
        
        if (abc.cross(ac).dot(ao) > 0) {
            if (ac.dot(ao) > 0) {
                supports = {A, C};
                direction = ac.cross(ao).cross(ac);
            } else {
                supports = {A, B};
                return line_case(supports, direction);
            }
        } else if (ab.cross(abc).dot(ao) > 0) {
            supports = {A, B};
            return line_case(supports, direction);
        } else {
            return true;
        }
        
        return false;
    }
}