#ifndef SETUP_HPP
#define SETUP_HPP
#include "config.hpp"

#include "fourier.hpp"

class Setup
{
protected:
    double U,V;
public:
    double getU() const { return U; }
    double getV() const { return V; }
    Setup(double u, double v) : U(u), V(v) {}
    Setup(const Setup&) = delete;
    virtual ~Setup() {}
    virtual void set(const double newU, const double newV) = 0;
    virtual Fourier::spec_t green(double,int) = 0;
};

#endif // guard
