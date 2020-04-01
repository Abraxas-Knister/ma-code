/* set state of qcomputer to product state
 * encoded by mask
 * with no phase
 */
Rig& Rig::set(int mask)
{
    if (mask<0 && mask>= m_length)
          throw std::runtime_error("Can't set the mask");
    for (int i=0; i < m_length; ++i )
          m_memory[i] = 0.0;
    m_memory[mask] = 1.0 ;
    return *this;
}
// bounds check
void Rig::oob(int index)
{
    if (index < 0 || index >= m_bits)
          throw std::runtime_error("Index out of bounds");
}
// Constructor
Rig::Rig(int size)
    : m_bits(size) ,
      m_length(1 << size)
{
    if (!size)
          throw std::runtime_error("Trying to create empty quantum rig");

    m_memory = new complex[m_length];
    set();
}
// Destructor
Rig::~Rig()
{
    delete[] m_memory;
}
// looping for one spin operators
void Rig::loop(int index, void (*f)(complex&,complex&))
{
    oob(index);
    int mask = 1 << index;
    for (int i=0; i < m_length; ++i)
    {
        if (i & mask)
        {
            complex up = m_memory[i];
            complex dw = m_memory[i & ~mask];
            if (std::norm(up) + std::norm(dw) <= absEps)
                  continue;
            f(up,dw);
            m_memory[i] = up;
            m_memory[i & ~mask] = dw;
        }
    }
}
// looping for two spin operators
void Rig::ctrl(int index, void (*f)(complex&,complex&), int by, bool ifset)
{
    oob(index); oob(by);
    const int mask = 1 << index;
    const int cmask = 1 << by;
    auto check
    { [&] (int i) -> bool
        {
            if (ifset)
                    return (i & (mask)) && (i & cmask);
            else
                    return (i & mask) && !(i & cmask);
        }
    };
    for (int i=0; i < m_length; ++i) // duplicate code!
    {
        if (check(i)) // apart from this here
        {
            complex up = m_memory[i];
            complex dw = m_memory[i & ~mask];
            if (std::norm(up) + std::norm(dw) <= absEps)
                  continue;
            f(up,dw);
            m_memory[i] = up;
            m_memory[i & ~mask] = dw;
        }
    }
}
// printing
std::ostream& operator<< (std::ostream& out,const Rig& r)
{
    for (int i=0; i < r.m_length - 1; ++i)
          out << bin(i , r.m_bits) << " : " << r.m_memory[i] << '\n';
    return out;
}
