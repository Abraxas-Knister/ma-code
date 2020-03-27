#ifndef QC_HPP
#define QC_HPP
#include "config.hpp"

#include "qbit.hpp"

namespace QC
{
    class Rig
    {
        Qbit * m_mem;
        int m_size;
        void oob (int);
    public:
        Rig(int);
        virtual ~Rig();

        Rig& X(int);
        Rig& Y(int);
        Rig& Z(int);

        Rig& M(int);
        Rig& P(int);
        Rig& H(int);
        // Rig& U(int,Unitary);

        // Jordan Wigner creator/annihilator
        Rig& JWA(int);
        Rig& JWC(int);

        const Qbit& get(int index) { oob(index); return m_mem[index]; }
        int size() { return m_size; }
    };
}

#endif // guard
