#include "greensfunction.hpp"

m_gf::m_gf(Setup &s)
{
    setup = &s;
}

void m_gf::compute(const double begin, const double end, const double step)
{
    time.clear(); real0.clear(); imag0.clear(); real1.clear(); imag1.clear();
    m_state_t gd = setup->gdstate();
    for (int orb = 0; orb < 2; orb++ )
    {
        for (double t=begin; t<end; t+=step)
        {
            setup->state = gd;
            setup->actWithCd(orb);
            setup->evolve(t);
            setup->actWithC(orb);
            setup->evolve(-t);
            complex goft = gd.dot(setup->state);
            if (orb)
            {
                time.push_back(t);
                real1.push_back(goft.real());
                imag1.push_back(goft.imag());
            } else {
                real0.push_back(goft.real());
                imag0.push_back(goft.imag());
            }
        }
    }
}

std::ostream& operator<< (std::ostream &out, const m_gf &gf)
{
    for (int i=0; i<gf.time.size(); i++)
    {
        out << gf.time[i] << ' ' 
            << gf.real0[i] << ' ' << gf.imag0[i] << ' '
            << gf.real1[i] << ' ' << gf.imag1[i] << '\n';
    }
    return out;
}
