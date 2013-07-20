#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include "primitive_logic_types.h"

#include <unordered_map>
#include <unordered_set>
#include <string>

namespace fol {

class SymbolTable
{
    //stores any kind of descriptor for a term
    //only necessary when parsing
    std::map<std::string, ast_node*> descriptors;
    int skolem_count;

public:
    ast_node* insert(ast_node_type t, const std::string& s);
    SymbolTable();
};

}

#endif // SYMBOL_TABLE_HPP
