#ifndef QC_HPP
#define QC_HPP
#include "config.hpp"

#include <functional>
#include <iostream>

namespace QC { class Rig; }
std::ostream& operator<< (std::ostream&,const QC::Rig&);

namespace QC
{
    using unitary = void (complex&,complex&);
    class Rig
    {
        const int m_bits;
        const int m_length;
        complex * m_memory;
        void oob(int index);
    public:
        Rig(int);
        virtual ~Rig();

        Rig& set(int=0);
        Rig& prob(int,double&,double&);

        friend
        std::ostream& (::operator<<) (std::ostream&,const Rig&);

        Rig& gate(int, std::function<unitary>, int=-1, bool=true);
        Rig& gate(int, std::function<unitary>, double, int=-1, bool=true);
    };
    unitary X, Y, Z, H;
}

#endif // guard
