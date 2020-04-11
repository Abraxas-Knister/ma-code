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

// printing
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
