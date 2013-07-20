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
#include "../fol/symbol_table.hpp"
#include "../fol/clausification.hpp"
#include "../fol/primitive_logic_types.h"

#include <istream>
#include <fstream>

class parser
{
    using namespace fol;

    SharedTermBank& m_shr;
    SymbolTable& m_sym;
    std::vector<ast_node*>& m_frm;
    std::istream& m_is;

public:
    parser(SharedTermBank& shr, SymbolTable& sym, std::vector<ast_node*>& frm,
           const char* problem_file);
    void operator()();
};

#endif // PARSER_HPP
