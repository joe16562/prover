#include "primitive_logic_types.h"

/**********************************************************
 *  Author:   Joseph Lawrie 16562@faith.sa.edu.au
 *  Date:     16 June 2013
 *
 *  This file contains defintions for the basic
 *  structures used throughout the prover
 *
 *  A generic formula is represented by an
 *  abstract syntax tree. Each node inherits from
 *  node_type, which encodes the type of node and
 *  a descriptor of the node for term nodes
 *
 *********************************************************/

namespace fol{

child* new_function(const descriptor* d, unsigned int i, const child** c );
child* new_function(const descriptor* d, const child** c );

child* new_predicate(const descriptor* d, const child** c );
child* new_predicate(const descriptor* d, unsigned int i, const child** c );

child* new_constant(const descriptor* d);
child* new_variable(const descriptor* d);

child* new_negated_formula(const child* f);
child* new_connective(const child* f, node_type t,const child* f);
child* new_quantified(node_type t, const descriptor* d, const child* f);
child* new_equational_lit(const child* lt, node_type t, const child* rt);

} // namespace fol
