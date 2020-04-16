// printing
std::string bin(int m, int width)
{
    if (width <= 0) return "";
    std::string c = "";
    if ( m & (1 << (width-1)) )
          c = "u";
    else { c = "d"; }
    return c + bin(m,width-1);
}
std::ostream& operator<< (std::ostream& out,const Rig& r)
{
    for (int i=0; i < r.m_length - 1; ++i)
          out << bin(i , r.m_bits) << " : " << r.m_memory[i] << '\n';
    return out;
}
/* measure the X,Y,Z projection of spin "index" without projecting
 * load the doubles m and p with the probabilities for eigenvalue -1 / + 1
 */
const Rig& Rig::probX(int index, double& m, double& p) const
{
    /* sqrt(1/2) (X+Z) is the transform between Z and X and back
     *
     * -> +1 part is (up+dw)/sqrt(2)
     *    -1 is (dw-up)/sqrt2
     */
    oob(index);
    m = 0.0;
    int mask = 1 << index;
    for (int i=0; i<m_length; ++i)
    {
        if (i & mask)
        {
            complex
                up = m_memory[i],
                dw = m_memory[i & ~mask];
            m += std::norm(dw-up);
        }
    }
    m /= 2.0;
    p = 1.0 - m;
    return *this;
}
const Rig& Rig::probY(int index, double& m, double& p) const
{
    /* sqrt(1/2) (Y+Z) is the transform between Z and Y and back
     *
     * -> +1 part is (dw - i up)/sqrt(2)
     *    -1 is (i dw - up)/sqrt2
     */
    oob(index);
    m = 0.0;
    int mask = 1 << index;
    for (int i=0; i<m_length; ++i)
    {
        if (i & mask)
        {
            complex
                up = m_memory[i],
                dw = m_memory[i & ~mask];
            m += std::norm(dw-IU*up);
        }
    }
    m /= 2.0;
    p = 1.0 - m;
    return *this;
}
const Rig& Rig::probZ(int index, double& m, double& p) const
{
    oob(index);
    m = 0.0;
    int mask = 1 << index;
    for (int i=0; i<m_length; ++i)
    {
        if (i & mask)
              m += std::norm(m_memory[i]);
    }
    p = 1.0 - m;
    return *this;
}
