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
#include "qc-3.inl"
