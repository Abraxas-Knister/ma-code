// helpers
void _X (complex& up, complex& dw)
{
    auto tmp = up;
    up = dw;
    dw = tmp;
}
void _Y (complex& up, complex& dw)
{
    auto tmp = up;
    up = IU*dw;
    dw = -IU*tmp;
}

void _Z (complex& up, complex&)
{
    up *= -1.0;
}

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
void _H (complex& up, complex& dw)
{
    static constexpr double sq2inv = 0.7071067811865475244008443621048490392848 ;
    auto u = dw - up;
    auto d = dw + up;
    up = u*sq2inv;
    dw = d*sq2inv;
}

namespace QC { double _rotation; }
void _R(complex &up,complex&)
{
    up *= std::exp(_rotation*PI*IU);
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

