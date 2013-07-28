#ifndef CLAUSIFICATION_HPP
#define CLAUSIFICATION_HPP

/**********************************************************
 *  Author:   Joseph Lawrie 16562@faith.sa.edu.au
 *  Date:     16 June 2013
 *  Modified: 20 July 2013
 *
 *  Contains defintions of functions for converting formulae
 *  to CNF form, suitable for the theorem prover.
 *
 *  Any new variables or constants added will have an
 *  invalid pointer for a descriptor
 *
 *********************************************************/

#include "primitive_logic_types.h"
#include "substitutions.hpp"
#include "utilities.hpp"
#include "../system/prover.hpp"

#include <vector>
#include <unordered_set>
#include <stack>

namespace fol {

void ConvertToCnf(FormulaList formulae,ClauseList clauses, Prover& proof_context);

}

#endif // CLAUSIFICATION_HPP
