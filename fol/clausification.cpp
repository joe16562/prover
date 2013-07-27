#include "clausification.hpp"
#include <cassert>

namespace fol {

/**********************************************************
 *  Copies an ast, used during conversion to cnf, all terms
 *  have been replaced by descriptors at this point
 *********************************************************/

child* copy(const child* child_to_copy){
    switch(child_to_copy->getType()){
    case NEGATED_FORMULA: //recursive copy of subtree
        return new_negated_formula(
                    copy(child_to_copy[1].getSubFormula()));
        break;

    case PREDICATE: //non-recursive copy because of shared terms
        return new_predicate(
                    child_to_copy[0].getDescriptor(),
                    child_to_copy[1].getArrity(),
                    &child_to_copy[2]);
        break;

    case CONNECTIVE_OR: //recursive copy of subtrees
    case CONNECTIVE_AND:
    case CONNECTIVE_IFF:
    case CONNECTIVE_IMP:
        return new_connective(
                    copy(child_to_copy[1].getSubFormula()),
                    child_to_copy[0].getType(),
                    copy(child_to_copy[2].getSubFormula())
                );
        break;

    case QUANTIFIER_EXI:
    case QUANTIFIER_UNI:
        return new_quantified(
                    child_to_copy[0].getType(),
                    child_to_copy[0].getDescriptor(),
                    child_to_copy[1].getSubFormula()
                );
        break;

    case EQUATIONAL_LIT_NEG:
    case EQUATIONAL_LIT_POS:
        return new_equational_lit(
                    child_to_copy[0].getSubTerm(),
                    child_to_copy[0].getType(),
                child_to_copy[1].getSubTerm()
                );
        break;

    case FUNCTION:
    case CONSTANT:
    case VARIABLE:
        assert(term->getType() != FUNCTION
               || term->getType() != VARIABLE
               || term->getType() != CONSTANT);
        break;
    default:
        assert(false);
    }
}

child* standardise_variables(const FormulaList* formulae, uintptr_t& next_id){
    std::unordered_set<uintptr_t> used_variables;
    for(auto formula_it = formulae->begin(); formula_it != formulae->end(); formula_it++)
    {
        child* formula = *formula_it;
        switch(formula->getType()){
        case VARIABLE: //check if it's been used
            if(used_variables.insert(id).second == true){
                // variable is new
            } else {
                formula->setDescriptor(next_id);
                next_id += 4;
            }


        }
    }
}

/*
    FUNCTION = 0,
    CONSTANT = 1,
    VARIABLE = 2,
    FORMULA = 3,

    //why start not from 0?
    NEGATED_FORMULA = (1 << 2) + FORMULA,
    PREDICATE       = (2 << 2) + FORMULA,
    CONNNECTIVE_OR  = (3 << 2) + FORMULA,
    CONNECTIVE_AND  = (4 << 2) + FORMULA,
    CONNECTIVE_IMP  = (5 << 2) + FORMULA,
    CONNECTIVE_IFF  = (6 << 2) + FORMULA,
    QUANTIFIER_UNI  = (7 << 2) + FORMULA,
    QUANTIFIER_EXI  = (8 << 2) + FORMULA,
    EQUATIONAL_LIT  = (9 << 2) + FORMULA

    */

struct reducer{
    void operator(){

    }
};

struct standardiser{
    void operator(){

    }
};

struct skolemizer{
    void operator(){

    }
};

struct distributer{
    void operator(){

    }
};




void clausify(FormulaList* formula,ClauseList* c, );

}
