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
        void oob(int index) const;
    public:
        Rig(int);
        virtual ~Rig();

        Rig& set(int=0);
        complex* bad() { return m_memory; }
        /* bad() is black magic since it allows the state to be overwritten
         * arbitrarily (by something outside) as opposed to being manipulated
         * well defined (and norm conserving) through gates.
         *
         * -> should be removed ASAP
         */
        const Rig& probX(int,double&,double&) const;
        const Rig& probY(int,double&,double&) const;
        const Rig& probZ(int,double&,double&) const;

        friend
        std::ostream& (::operator<<) (std::ostream&,const Rig&);

        Rig& gate(int, std::function<unitary>, int=-1, bool=true);
        Rig& gate(int, std::function<unitary>, double, int=-1, bool=true);

        friend class Stash;
        /* this class can store a state and reintroduce it to speed up some
         * things
         */
    };
    unitary X, Y, Z, H;
}

#endif // guard
