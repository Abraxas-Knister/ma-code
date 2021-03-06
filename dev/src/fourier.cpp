#include "fourier.hpp"
#include <unsupported/Eigen/FFT>

Fourier::Fourier (std::size_t s)
    : m_samples(0), m_step(0.0)
{
    m_valsTime.reserve(s);
    m_valsFreq.reserve(s);
    m_specTime.reserve(s);
    m_specFreq.reserve(s);
}

Fourier::Fourier (Fourier::spec_t& v, double step, bool time)
    : Fourier(v.size())
{ update(v,step,time); }

Eigen::FFT<double> _fft;
void Fourier::update(Fourier::spec_t& newSpec, double step, bool time)
{
    // create freq/time spectrum
    if (time)
    {
        m_specFreq.clear();
        m_specTime.swap(newSpec);
        _fft.fwd(m_specFreq,m_specTime);
    } else {
        m_specFreq.clear();
        m_specFreq.swap(newSpec);
        _fft.inv(m_specFreq,m_specTime);
    }
    if ( (newSpec.size()!=m_samples) || !areNear(step,m_step) )
    {
        m_step = step; m_samples = newSpec.size();
        // write timescale
        const std::size_t counts { m_specFreq.size() };
        m_valsTime.resize(counts);
        int ct=-1;
        for (auto& i : m_valsTime)
              i = ++ct * step; 
        // write freqscale
        m_valsFreq.resize(counts);
        const double f = 1.0/(counts*step);
        for (std::size_t i=0; i<counts; i++)
        {
            int j = ( i < counts/2 ? i : i-counts);
            m_valsFreq[i] = f * j;
        }
    }
}

std::ostream& operator<< (std::ostream& out, const Fourier& f)
{
    for (std::size_t i=0; i<f.m_valsTime.size(); i++)
    {
        out
            << f.m_valsTime[i]          << ' '
            << f.m_specTime[i].real()   << ' '
            << f.m_specTime[i].imag()   << ' '

            << f.m_valsFreq[i]          << ' '
            << f.m_specFreq[i].real()   << ' '
            << f.m_specFreq[i].imag()   << '\n';
    }
    return out;
}
