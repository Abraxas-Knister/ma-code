#ifndef QCSTASH_HPP
#define QCSTASH_HPP
#include "config.hpp"

#include "qc.hpp"

namespace QC
{
    class Stash
    {
        Rig& m_rig;
        complex* m_sto;
    public:
        Stash (Rig& r)
            : m_rig(r),
              m_sto(nullptr)
        {}
        ~Stash() { delete[] m_sto; }
        void save()
        {
            if (m_sto) return;
            m_sto = new complex[m_rig.m_length];
            for (int i{ 0 }; i<m_rig.m_length; ++i)
                  m_sto[i] = m_rig.m_memory[i];
        }
        void apply()
        {
            if (!m_sto) return;
            delete[] m_rig.m_memory;
            m_rig.m_memory = m_sto;
            m_sto = nullptr;
        }
    };
}

#endif // guard
