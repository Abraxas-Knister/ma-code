#ifndef QC_HPP
#define QC_HPP
#include "config.hpp"

#include <iostream>

namespace QC {class Rig;}
std::ostream& operator<< (std::ostream&,const QC::Rig&);

namespace QC
{
    class Rig
    {
        const int m_bits;
        const int m_length;
        complex * m_memory;
        void oob(int index);
        void loop(int,void (*)(complex&,complex&));
    public:
        Rig(int);
        virtual ~Rig();

        friend
        std::ostream& (::operator<<) (std::ostream&,const Rig&);

        // Paulis
        Rig& X(int);
        Rig& Y(int);
        Rig& Z(int);

        // Hadamard and plus, minus
        Rig& H(int);
        Rig& M(int);
        Rig& P(int);

        // creation and annihilation of spin up/dw
        Rig& A(int);
        Rig& C(int);
    };
}

#endif // guard
