#include "simplex.h"

namespace Physics
{
    CSOSupport::CSOSupport() {}

    CSOSupport::CSOSupport(const Polygon* const a_poly, const Polygon* const b_poly, Vector2 d)
    {
        a = a_poly->support(d);
        b = b_poly->support(-1*d);
        c = a - b;
    }

    Simplex2::Simplex2()
        : m_size(0),
          m_contains_origin(false)
    {
    }

    Simplex2& Simplex2::operator=(std::initializer_list<CSOSupport> points)
    {
        for (const CSOSupport* point = points.begin(); point != points.end(); point++) {
            m_points[std::distance(points.begin(), point)] = *point;
        }
        m_size = points.size();

        return *this;
    }

    void Simplex2::push_front(CSOSupport point)
    {
        m_points = {point, m_points[0], m_points[1]};
        if (m_size < 3) m_size++;
    }

    CSOSupport& Simplex2::operator[](unsigned i) { return m_points[i]; }
    unsigned Simplex2::size() const {return m_size; }

    void Simplex2::set_contains_origin()
    {
        m_contains_origin = true;
    }

    bool Simplex2::contains_origin() const
    {
        return m_contains_origin;
    }
}