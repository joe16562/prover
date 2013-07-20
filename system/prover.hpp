#ifndef PROVER_HPP
#define PROVER_HPP

#include "parser.hpp"

#include "../fol/shared_term_bank.h"
#include "../fol/symbol_table.hpp"
#include "../fol/clausification.hpp"

#include <unordered_set>
#include <queue>


using namespace fol;

class Prover
{
    SharedTermBank shr;
    SymbolTable sym;

    std::vector<clause> clauses;
    std::unordered_set<clause> passive;
    std::unordered_set<clause> current;
    std::unordered_set<clause> active;
    std::unordered_set<clause> active;

public:
    Prover(const char* problem_file);
    bool givenClause();
};

#endif // PROVER_HPP
