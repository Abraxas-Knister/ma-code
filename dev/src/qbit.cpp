#include "qbit.hpp"

#include <algorithm>
#include <cmath> 
#include <iostream>

using namespace QC;

void Qbit::renorm()
{
    if (!*this)
          return;
    double norm = 1.0/std::sqrt( std::norm(m_up) + std::norm(m_dw) );
    std::cout << norm << '\n';
    m_up *= norm;
    m_dw *= norm;
}

Qbit::operator bool ()
{
    return m_up.real() || m_up.imag() || m_dw.real() || m_dw.imag();
}

Qbit& Qbit::X()
{
    std::swap(m_up,m_dw);
    return *this;
}

Qbit& Qbit::Y()
{
    std::swap(m_up,m_dw);
    m_dw *= -IU;
    m_up *= IU;
    return *this;
}

Qbit& Qbit::Z()
{
    m_up *= -1.0;
    return *this;
}

Qbit& Qbit::M()
{
    /* X - i Y (d , u)
     * = (u , d) - i (-i u , i d)
     * = (u , d) - (u , -d)
     * = (0 , 2d)
     * M(d,u) = (0,d)
     */
    m_up = 0.0;
    std::swap(m_up,m_dw);
    return *this;
}

Qbit& Qbit::P()
{
    m_dw = 0.0;
    std::swap(m_up,m_dw);
    return *this;
}

Qbit& Qbit::H()
{
    auto up = m_dw - m_up;
    auto dw = m_dw + m_up;
    m_up = up;
    m_dw = dw;
    renorm();
    return *this;
}

std::ostream& operator<< (std::ostream& out , const Qbit& q)
{
    out << "Qbit( " << q.m_dw << " , " << q.m_up << " )";
    return out;
}
