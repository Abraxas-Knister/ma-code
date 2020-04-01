// === One Bit ===
// Paulis
Rig& Rig::X(int index)
{
    loop(index , _X);
    return *this;
}


Rig& Rig::Y(int index)
{
    loop(index , _Y);
    return *this;
}
Rig& Rig::Z(int index)
{
    loop(index , _Z);
    return *this;
}
// Hadamard and plus, minus
Rig& Rig::H(int index)
{
    loop(index, _H);
    return *this;
}
Rig& Rig::M(int index)
{
    loop(index, _M);
    return *this;
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
// rotation
Rig& Rig::R(int index, double pimul, Rig& (Rig::*pauli)(int))
{
    const auto cos = std::cos(PI*pimul);
    const auto sin = IU*std::sin(PI*pimul);

    complex *copy = new complex[m_length];
    for (int i=0; i<m_length; ++i)
          copy[i] = m_memory[i];

    (this->*pauli)(index);
    for (int i=0; i<m_length; ++i) 
          m_memory[i] = copy[i] * cos + m_memory[i] * sin;
    delete[] copy;
    return *this;
}
// === Two Bit ===
// Controlled Z
Rig& Rig::CZ(int index,int by, bool ifset)
{
    ctrl(index,_Z,by,ifset);
    return *this;
}
// controlled rotation
Rig& Rig::CR(int index, double pimul, int by, bool ifset)
{
    _rotation = pimul;
    ctrl(index,_R,by,ifset);
    return *this;
}
