#include "qc.hpp"
#include "qbit.hpp"
#include <cassert>

using namespace QC;

void Rig::oob(int index)
{
    assert( 0 <= index && index < m_size && "Index out of bounds");
}

Rig::Rig(int N)
    : m_mem(nullptr)
{
    assert(0 < N && "Attempting to create empty Quantum Rig");
    m_mem = new Qbit[N];
    m_size = N;

    for (int i=0; i<m_size; ++i)
    {
        m_mem[i] = Qbit::O();
    }
}

Rig::~Rig()
{
    delete[] m_mem;
}

Rig& Rig::X(int index)
{
    oob(index);
    m_mem[index].X();
    return *this;
}

Rig& Rig::Y(int index)
{
    oob(index);
    m_mem[index].Y();
    return *this;
}

Rig& Rig::Z(int index)
{
    oob(index);
    m_mem[index].Y();
    return *this;
}

Rig& Rig::M(int index)
{
    oob(index);
    m_mem[index].M();
    return *this;
}

Rig& Rig::P(int index)
{
    oob(index);
    m_mem[index].P();
    return *this;
}

Rig& Rig::H(int index)
{
    oob(index);
    m_mem[index].H();
    return *this;
}

Rig& Rig::JWA(int index)
{
    oob(index);
    m_mem[index].P();
    for (int i{ index - 1 }; i >= 0 ; --i)
          m_mem[i].Z();
    return *this;
}

Rig& Rig::JWC(int index)
{
    oob(index);
    m_mem[index].M();
    for (int i{ index - 1 }; i >= 0 ; --i)
          m_mem[i].Z();
    return *this;
}

