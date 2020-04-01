#ifndef QC_HPP
#define QC_HPP
#include "config.hpp"

#include <iostream>

namespace QC { class Rig; }
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
        void ctrl(int, void (*)(complex&,complex&), int, bool);
    public:
        Rig(int);
        virtual ~Rig();

        Rig& set(int=0);

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

        // rotation
        Rig& R(int,double,Rig& (Rig::*)(int)=&Rig::Z);

        // Controlled gates
        Rig& CZ(int,int,bool=true);
        Rig& CR(int,double,int,bool=true);
    };
}

#endif // guard
