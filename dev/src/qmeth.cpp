#include "qmeth.hpp"

#include "dense-ed.hpp"
#include "gates.hpp"
#include "qc-stash.hpp"

#include <map>

#include "qmeth-interfer.inl"
/* everything needed to
 * compute single timesteps through interferometry
 * 
 * Greensfunction is comprised of summands of the form
 * <U^+ P U S> where P,S are pauli gates.
 *
 * such a summand can be computed for a certain time point
 * ( given by an int and a double )
 * by part(). full() adds all the necessary <U^+ P U S> parts
 * to obtain the full G
 *
 * the groundstate related to the parameters U and V is prepared by
 * prepare()
 */
#include "qmeth-trotter.inl"
/* everything needed to implement
 * a time evolution operator needed for the interferometry
 */
#include "qmeth-setup.inl"
/* all the parts necessary for class Qmeth to be a class Setup
 * ie green() which gives back a greensfunction
 * and set() which enables giving back that greensfunction
 */
