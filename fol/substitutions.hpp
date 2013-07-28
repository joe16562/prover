#ifndef SUBSTITUTIONS_HPP
#define SUBSTITUTIONS_HPP

#include "primitive_logic_types.h"
#include <unordered_map>
//#include <tuple>

namespace fol{

typedef std::pair<child*,child*> Substitution;
typedef std::unordered_map<child*,child*> SubstitutionList;

}

#endif // SUBSTITUTIONS_HPP
