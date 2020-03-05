#include "greensfunction.hpp"

m_gf::m_gf(Setup &s)
{
    setup = &s;
}

void m_gf::compute(const double begin, const double end, const double step)
{
    time.clear(); timedep0.clear(); timedep1.clear(); freqdep0.clear(); freqdep1.clear();
    m_state_t gd = setup->gdstate();
    for (int orb = 0; orb < 2; orb++ )
    {
        for (double t=begin; t<end; t+=step)
        {
            // first Cd then C
            setup->state = gd;
            setup->actWithCd(orb);
            setup->evolve(t);
            setup->actWithC(orb);
            setup->evolve(-t);
            complex goft = gd.dot(setup->state);
            // first C then Cd
            setup->state = gd;
            setup->evolve(t);
            setup->actWithCd(orb);
            setup->evolve(-t);
            setup->actWithC(orb);
            goft += gd.dot(setup->state);
            goft /= IU;
            if (orb)
            {
                time.push_back(t);
                timedep1.push_back(goft);
            } else {
                timedep0.push_back(goft);
            }
        }
    }
}

std::ostream& operator<< (std::ostream &out, const m_gf &gf)
{
    for (int i=0; i<gf.time.size(); i++)
    {
        out << gf.time[i] << ' ' 
            << gf.timedep0[i].real() << ' ' << gf.timedep0[i].imag() << ' '
            << gf.timedep1[i].real() << ' ' << gf.timedep1[i].imag() << '\n';
    }
    return out;
}
