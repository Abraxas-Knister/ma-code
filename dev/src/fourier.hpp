#ifndef FOURIER_HPP
#define FOURIER_HPP
#include "config.hpp"

#include <ostream>
#include <vector>

class Fourier;
std::ostream& operator<< (std::ostream& , const Fourier&);

class Fourier
{
public:
    using vals_t = std::vector<double>;
    using spec_t = std::vector<complex>;
private:
    int m_samples;
    double m_step;
    vals_t m_valsTime;
    vals_t m_valsFreq;
    spec_t m_specTime;
    spec_t m_specFreq;
public:
    const vals_t& valsTime() const { return m_valsTime; }
    const vals_t& valsFreq() const { return m_valsFreq; }
    const spec_t& specTime() const { return m_specTime; }
    const spec_t& specFreq() const { return m_specFreq; }

    Fourier (std::size_t s);
    Fourier (spec_t&,double,bool=true);
    void update(spec_t&,double,bool=true);

    friend
    std::ostream& operator<< (std::ostream& , const Fourier&);
};

#endif // guard
