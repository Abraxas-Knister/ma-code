#include "qc.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace QC;

void Rig::oob(int index)
{
    if (index < 0 || index >= m_bits)
          throw std::runtime_error("Index out of bounds");
}

Rig::Rig(int size)
    : m_bits(size) ,
      m_length(1 << size)
{
    if (!size)
          throw std::runtime_error("Trying to create empty quantum rig");

    m_memory = new complex[m_length];
    for (int i=0; i < m_length; ++i )
          m_memory[i] = 0.0;
    m_memory[0] = 1.0 ;
}

Rig::~Rig()
{
    delete[] m_memory;
}

void Rig::loop(int index, void (*f)(complex&,complex&))
{
    oob(index);
    int mask = 1 << index;
    for (int i=0; i < m_length; ++i)
    {
        if (i & mask)
        {
            complex up = m_memory[i];
            complex dw = m_memory[i & ~mask];
            if (std::norm(up) + std::norm(dw) <= absEps)
                  continue;
            f(up,dw);
            m_memory[i] = up;
            m_memory[i & ~mask] = dw;
        }
    }
}

// Paulis
void _X (complex& up, complex& dw)
{
    auto tmp = up;
    up = dw;
    dw = tmp;
}
Rig& Rig::X(int index)
{
    loop(index , _X);
    return *this;
}

void _Y (complex& up, complex& dw)
{
    auto tmp = up;
    up = IU*dw;
    dw = -IU*tmp;
}
Rig& Rig::Y(int index)
{
    loop(index , _Y);
    return *this;
}

void _Z (complex& up, complex&)
{
    up *= -1.0;
}
Rig& Rig::Z(int index)
{
    loop(index , _Z);
    return *this;
}

// Hadamard and plus, minus
void _H (complex& up, complex& dw)
{
    static constexpr double sq2inv = 0.7071067811865475244008443621048490392848 ;
    auto u = dw - up;
    auto d = dw + up;
    up = u*sq2inv;
    dw = d*sq2inv;
}
Rig& Rig::H(int index)
{
    loop(index, _H);
    return *this;
}
void _M (complex& up, complex& dw)
{
    up = dw;
    dw = 0.0;
}
Rig& Rig::M(int index)
{
    loop(index, _M);
    return *this;
}
void _P (complex& up, complex& dw)
{
    dw = up;
    up = 0.0;
}
Rig& Rig::P(int index)
{
    loop(index, _P);
    return *this;
}
// creation and annihilation of spin up/dw
Rig& Rig::A(int index)
{
    P(index);
    for (int i = 0; i<index; ++i)
          Z(i);
    return *this;
}

Rig& Rig::C(int index)
{
    M(index);
    for (int i = 0; i<index; ++i)
          Z(i);
    return *this;
}

std::string bin(int m, int width)
{
    if (width <= 0) return "";
    std::string c = "";
    if ( m & (1 << (width-1)) )
          c = "u";
    else { c = "d"; }
    return c + bin(m,width-1);
}

std::ostream& operator<< (std::ostream& out,const Rig& r)
{
    for (int i=0; i < r.m_length - 1; ++i)
          out << bin(i , r.m_bits) << " : " << r.m_memory[i] << '\n';
    return out;
}
