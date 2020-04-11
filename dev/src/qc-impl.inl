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
/* measure the Z projection of spin "index" without projecting
 * load the double pup and pdw with the probabilities for up and dw
 */
Rig& Rig::prob(int index, double& up, double& dw)
{
    oob(index);
    up=0.0;
    int mask = 1 << index;
    for (int i=0; i<m_length; ++i)
    {
        if (i & mask)
              up+=std::norm(m_memory[i]);
    }
    dw=1.0-up;
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
