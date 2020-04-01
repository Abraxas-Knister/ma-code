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
