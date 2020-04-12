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
