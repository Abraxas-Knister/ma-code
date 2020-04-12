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
