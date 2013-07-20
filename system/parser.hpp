#ifndef PARSER_HPP
#define PARSER_HPP

/**********************************************************
 *  Author:   Joseph Lawrie 16562@faith.sa.edu.au
 *  Date:     16 June 2013
 *
 *  This file constains the interface to the parser, which
 *  is designed to read the problem from the input and
 *  reconstruct it in memory
 *********************************************************/

#include "../fol/shared_term_bank.h"
#include "../fol/clausification.hpp"
#include "../fol/primitive_logic_types.h"

#include <iostream>
#include <string>
#include <unordered_map>

class parser
{
    using namespace fol;

    SharedTermBank& shared_term_bank;
    std::unordered_map<std::string,descritor*> constants;
    std::unordered_map<std::string,descritor*> variables;
    std::vector<ast_node*>& formulae;
    std::istream& input;

public:
    parser(SharedTermBank& shr, SymbolTable& sym, std::vector<ast_node*>& frm,
           const char* problem_file);
    void parse();
};

#endif // PARSER_HPP
