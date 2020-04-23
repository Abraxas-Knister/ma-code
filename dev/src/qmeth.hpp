#ifndef QMETH_HPP
#define QMETH_HPP
#include "config.hpp"

#include "setup.hpp"
#include "qc.hpp"

class Qmeth : public Setup
{
    QC::Rig* rig;
    Qmeth& prepare();
    Qmeth& trotterstep(double);
    Qmeth& evolve(double,int);
    complex part(QC::unitary*,QC::unitary*,double,int);
    complex full(double,int);
public:
    Qmeth(double u, double v) : Setup(u,v) , rig(new QC::Rig(5)) {}
    ~Qmeth() { delete rig; }
    void set(const double newU, const double newV)  override ;
    Fourier::spec_t green(double,int)               override ;
};

#endif // guard
