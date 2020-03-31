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
    set();
}

Rig::~Rig()
{
    delete[] m_memory;
}

Rig& Rig::set(int mask)
{
    if (mask<0 && mask>= m_length)
          throw std::runtime_error("Can't set the mask");
    for (int i=0; i < m_length; ++i )
          m_memory[i] = 0.0;
    m_memory[mask] = 1.0 ;
    return *this;
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

#include "qc-2.inl"
