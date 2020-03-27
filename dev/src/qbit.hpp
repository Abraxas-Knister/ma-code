#ifndef QBIT_HPP
#define QBIT_HPP
#include "config.hpp"

#include <iostream>

namespace QC {class Qbit;}
std::ostream& operator<< (std::ostream&, const QC::Qbit&);

namespace QC
{
    // class Unitary;
    class Qbit
    {
        complex m_up;
        complex m_dw;
        void renorm();
    public:
        Qbit(complex dw=0.0, complex up=0.0)
            : m_up(up), m_dw(dw)
        {
            renorm();
        }

        Qbit (double dw,double up)
            : Qbit(static_cast<complex>(dw) , up)
        {}

        Qbit (const Qbit& q)
            : m_up(q.m_up) , m_dw (q.m_dw)
        {}

        operator bool ();

        Qbit& X ();  // Pauli matrices
        Qbit& Y ();
        Qbit& Z ();

        Qbit& M ();  // "Minus" = X - i Y
        Qbit& P ();  // "Plus"  = X + i Y
        Qbit& H ();
        //Qbit& U (complex,complex,complex,complex); generic unitary

        static Qbit O() { return Qbit( 1.0 , 0.0 ); }
        static Qbit I() { return Qbit( 0.0 , 1.0 ); }

        friend
        std::ostream& (::operator<<) (std::ostream&, const QC::Qbit&);
    };
}

#endif // guard
