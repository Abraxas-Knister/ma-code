#include "qc.hpp"

#include <cmath>
#include <functional>
#include <iostream>
#include <omp.h>
#include <stdexcept>
#include <string>

using namespace QC;

#include "qc-impl.inl"
/* class implementation:
 *
 * contructor, destructor
 * set function
 */
#include "qc-gates.inl"
/* gates are implemented as follows:
 * Rig::gate() takes 
 *  an index to apply the gate on
 *  a QC::unitary (aka void(complex&,complex&)
 *    transforming (up,dw) into the new (up,dw)
 *  an index to be controlled by
 *  a boolean wether the control should be 0 or 1
 *
 *  if the control is -1 no controlling is done
 *  if a double d is given as the third argument
 *   the Qbit is transformed as
 *    Id*cos(pi*d) + iP*sin(pi*d)
 *   where P is the provided unitary
 */
#include "qc-pauli.inl"
/*
 * QC::unitaries X,Y,Z,H
 */
#include "qc-misc.inl"
/* creators and annihilators, printing
 * prob function
 */
