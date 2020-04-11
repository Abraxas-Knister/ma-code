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
// "rotate" ie introduce phase between up and dw
std::function<unitary> QC::R(double pimul)
{
    complex phase { std::exp(IU*PI*pimul) };
    return
        [phase] (complex& up,complex&) -> void
        {
            up *= phase;
        }
    ;
}

// internal of the gates
Rig& Rig::gate(int index, std::function<unitary> f, int by, bool ifset)
{
    oob(index);
    const int mask = 1 << index;

    using check_t = std::function<bool(int)>;
    check_t check;

    if (by == -1)
    {
        check = {
            [&] (int i) -> bool
            {
                return i & mask;
            }
        };
    } else {
        oob(by);
        const int cmask = 1 << by;

        check = {
            [&] (int i) -> bool
            {
                if (ifset)
                        return (i & mask) && (i & cmask);
                else
                        return (i & mask) && !(i & cmask);
            }
        };
    }

    for (int i=0; i < m_length; ++i)
    {
        if (check(i))
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
    return *this;
}
Rig& Rig::gate(int index, std::function<unitary> f, double pimul, int by, bool ifset)
{
    /* exp ( i PI*pimul f) =
     *  cos(PI*pimul)ID + IU*sin(PI*pimul) f
     */
    const auto cos =    std::cos(PI*pimul);
    const auto sin = IU*std::sin(PI*pimul);

    std::function<unitary> rotation = {
        [&] (complex& up, complex& dw) -> void
        {
            complex b_up{up},b_dw{dw};
            f(up,dw);
            up = cos*b_up + sin*up;
            dw = cos*b_dw + sin*dw;
        }
    };
    return gate(index,rotation,by,ifset);
}
