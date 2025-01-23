#include "gjk.h"

namespace Physics
{
    static bool update_simplex(Simplex2& supports, Vector2& direction);
    static bool line_case(Simplex2& supports, Vector2& direction);
    static bool triangle_case(Simplex2& supports, Vector2& direction);

    Simplex2 GJK(const Polygon* const a, const Polygon* const b)
    {
        CSOSupport support(a, b, {1, 0});
        Simplex2 supports;
        supports.push_front(support);
        Vector2 direction = -1*support.c;
        
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

    static bool update_simplex(Simplex2& supports, Vector2& direction)
    {
        switch ( supports.size() ) {
            case 2: return line_case(supports, direction);
            case 3: return triangle_case(supports, direction);
        }
        
        return false; // Error
    }

    static bool line_case(Simplex2& supports, Vector2& direction)
    {

        CSOSupport A = supports[0];
        CSOSupport B = supports[1];

        Vector2 a = A.c;
        Vector2 b = B.c;
        
        Vector2 ab = b - a;
        Vector2 ao = -1*a;
        
        if (ab.dot(ao) > 0) {
            direction = ab.cross(ao).cross(ab);
        } else {
            supports = {A};
            direction = ao;
        }
        
        return false;
    }


    static bool triangle_case(Simplex2& supports, Vector2& direction)
    {
        CSOSupport A = supports[0];
        CSOSupport B = supports[1];
        CSOSupport C = supports[2];

        Vector2 a = A.c;
        Vector2 b = B.c;
        Vector2 c = C.c;

        Vector2 ab = b - a;
        Vector2 ac = c - a;
        Vector2 ao = -1*a;
        Vector2 abc = ab.cross(ac);
        
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