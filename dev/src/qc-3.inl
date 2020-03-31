// two index operators
void Rig::ctrl(int index, void (*f)(complex&,complex&), int by, bool ifset)
{
    oob(index); oob(by);
    const int mask = 1 << index;
    const int cmask = 1 << by;
    auto check
    { [&] (int i) -> bool
        {
            if (ifset)
                    return (i & (mask)) && (i & cmask);
            else
                    return (i & mask) && !(i & cmask);
        }
    };
    for (int i=0; i < m_length; ++i) // duplicate code!
    {
        if (check(i)) // apart from this here
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

// Controlled Z
Rig& Rig::CZ(int index,int by, bool ifset)
{
    ctrl(index,_Z,by,ifset);
    return *this;
}

// controlled rotation
namespace QC { double _rotation; }
void _R(complex &up,complex&)
{
    static const double pi = std::acos(-1);
    up *= std::exp(_rotation*pi*IU);
}
Rig& Rig::CR(int index, double pimul, int by, bool ifset)
{
    _rotation = pimul;
    ctrl(index,_R,by,ifset);
    return *this;
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
