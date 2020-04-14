#include "gates.hpp"

#include "random.hpp"

#include <cmath>

using namespace QC;

#include "gates-cre-ann.inl"
/* creation and annihilation operators
 * works by overloading operator+/-
 */
#include "gates-rot.inl"
#include "gates-twobit.inl"
/* implements the XX,YY,ZZ gates
 */
