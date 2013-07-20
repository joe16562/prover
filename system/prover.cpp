#include "prover.hpp"

using namespace fol;

class Prover
{
    SharedTermBank shr;
    SymbolTable sym;

    std::vector<ast_node*> formulas;
    std::vector<clause> clauses;
    std::unordered_set<clause> passive;
    std::unordered_set<clause> current;
    std::unordered_set<clause> active;
    std::unordered_set<clause> active;

public:
    Prover(const char* problem_file);
    bool givenClause();
};

Prover::Prover(const char* problem_file)
{
    parser psr(shr,sym,formulas,problem_file);
    psr();

    clausify(formulas,clauses,sym);

}

// attempt to refute the problem with the given clause algorithm
bool Prover::givenClause(){


}
