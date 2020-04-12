// pauli and hadamard gates
void QC::X (complex& up, complex& dw)
{
    auto tmp = up;
    up = dw;
    dw = tmp;
}
void QC::Y (complex& up, complex& dw)
{
    auto tmp = up;
    up = IU*dw;
    dw = -IU*tmp;
}
void QC::Z (complex& up, complex&)
{
    up *= -1.0;
}
void QC::H (complex& up, complex& dw)
{
    static constexpr double sq2inv = 0.7071067811865475244008443621048490392848 ;
    auto u = dw - up;
    auto d = dw + up;
    up = u*sq2inv;
    dw = d*sq2inv;
}
