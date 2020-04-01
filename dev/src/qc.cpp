#include "qc.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace QC;

#include "qc-helpers.inl"
/* funtions for the function pointer in the inner loop functions for the gates
 * binary number printing for the print rig operator<<
 */
#include "qc-impl.inl"
/* class implementation:
 *
 * contructor, destructor
 * set function
 * inner loops for the gates
 * printing
 */
#include "qc-gates.inl"
/* X Y Z H M P A C R-- single
 * CZ CR -- two 
 */
