#ifndef CLAUSIFICATION_HPP
#define CLAUSIFICATION_HPP

#endif // CLAUSIFICATION_HPP

#include "primitive_logic_types.h"
#include "utilities.hpp"

#include <vector>

namespace fol {
//  a clause is simply a vector of predicates and equality
//  literals, potentailly negated
typedef clause std::vector<ast_node*>;

void clausify(std::vector<ast_node*>& f,std::vector<clause>& c, SymbolTable& sym);

}
