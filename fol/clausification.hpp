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
#include "utilities.hpp"

#include <vector>
#include <unordered_set>

namespace fol {
//  a clause is simply a vector of predicates and equality
//  literals, potentailly negated
typedef std::vector<child*> clause;

void clausify(std::vector<ast_node*>& f,std::vector<clause>& c, SymbolTable& sym);

}

#endif // CLAUSIFICATION_HPP
