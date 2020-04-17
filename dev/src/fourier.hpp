#ifndef FOURIER_HPP
#define FOURIER_HPP
#include "config.hpp"

#include <iostream>
#include <unsupported/Eigen/FFT>
#include <vector>

class Fourier;
std::ostream& operator<< (std::ostream& , const Fourier&);

class Fourier
{
    std::vector<double>  m_valsTime;
    std::vector<double>  m_valsFreq;
    std::vector<complex> m_specTime;
    std::vector<complex> m_specFreq;
public:
    Fourier (std::size_t s);
    static Eigen::FFT<double> fft;
    void update(std::vector<complex>&,double,bool=true);

    friend
    std::ostream& operator<< (std::ostream& , const Fourier&);
};

#endif // guard
