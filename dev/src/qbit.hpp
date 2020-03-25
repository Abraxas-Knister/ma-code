#ifndef QBIT_HPP
#define QBIT_HPP
#include "config.hpp"

#include <iostream>

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

    operator bool ();

    Qbit& X ();
    Qbit& Y ();
    Qbit& Z ();
    Qbit& H ();

    friend
    std::ostream& operator<< (std::ostream& out , const Qbit&);
};

#endif // guard
