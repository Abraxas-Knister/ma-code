// creation and annihilation of spin up/dw
void _M (complex& up, complex& dw)
{
    up = dw;
    dw = 0.0;
}
void _P (complex& up, complex& dw)
{
    dw = up;
    up = 0.0;
}
Rig& operator- (Rig& r, int index)
{
    r.gate(index, _P);
    for (int i = 0; i<index; ++i)
          r.gate(i,Z);
    return r;
}
Rig& operator+ (Rig& r, int index)
{
    r.gate(index, _M);
    for (int i = 0; i<index; ++i)
          r.gate(i,Z);
    return r;
}
