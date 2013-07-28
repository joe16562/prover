#ifndef PROVER_HPP
#define PROVER_HPP

#include "parser.hpp"

#include "../fol/shared_term_bank.h"
#include "../fol/clausification.hpp"

#include <queue>
#include <unordered_set>
#include <unordered_map>

typedef std::unordered_map<std::string,uintptr_t> SymbolTable; // names->id
typedef std::unordered_map<unintptr_t,uintptr_t> LookupTable;  // id->arity
typedef std::vector<child*> FormulaList;

using namespace fol;

class Prover
{   
    // Memebers to manage
    SharedTermBank shared_term_bank;
    SymbolTable constants;
    SymbolTable variables;
    SymbolTable functions;
    SymbolTable predicates;
    LookupTable arrities;
    FormulaList* formulae;
    uintptr_t& next_id;

    std::vector<clause> clauses;
    std::unordered_set<clause> passive;
    std::unordered_set<clause> current;
    std::unordered_set<clause> active;

public:
    Prover(const char* problem_file);

    uintptr_t GetNextTermId(){next_id += 4; return id - 4;}

    bool GivenClause();
};

#endif // PROVER_HPP
