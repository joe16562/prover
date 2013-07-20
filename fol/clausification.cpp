#include "clausification.hpp"
#include <cassert>

namespace fol {

/**********************************************************
 *  This file make suse of the for_each_node template in
 *  utilities.hpp
 *********************************************************/

/**********************************************************
 *  Copies an ast, used during conversion to cnf, all terms
 *  have been replaced by descriptors at this point
 *********************************************************/

child* copy(const child* child_to_copy){
    switch(child_to_copy->getType()){
    case NEGATED_FORMULA: //recursive copy of subtree
        return new_negated_formula(
                    copy(child_to_copy[1].getSubFormula()));

    case PREDICATE: //non-recursive copy because of shared terms
        return new_predicate(
                    child_to_copy[0].getDescriptor(),
                    child_to_copy[1].getArrity(),
                    &child_to_copy[2]);

    case CONNECTIVE_OR: //recursive copy of subtrees
    case CONNECTIVE_AND:
    case CONNECTIVE_IFF:
    case CONNECTIVE_IMP:
        return new_connective(
                    copy(child_to_copy[1].getSubFormula()),
                    child_to_copy[0].getType(),
                    copy(child_to_copy[2].getSubFormula())
                );

    case QUANTIFIER_EXI:
    case QUANTIFIER_UNI:
        return new_quantified(
                    child_to_copy[0].getType(),
                child_to_copy[1].getSubTerm(),
                child_to_copy[2].getSubFormula()
                );

    case FUNCTION:
    case CONSTANT:
    case VARIABLE:
        assert(term->getType() != FUNCTION
               || term->getType() != VARIABLE
               || term->getType() != CONSTANT);
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

struct copier{
    std::vector<ast_node*> stack;

    void operator()(ast_node* n, traversal_enum t){
        if(t == FIRST) return;
        switch(n->getType()){
        //function can only be a predicate or function in the
        //shared term bank
        case FUNCTION:
            stack.push_back(n);

        }

    }
};

struct deleter{
    void operator(){

    }
};

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




void clausify(std::vector<ast_node*>& f,std::vector<clause>& c, SymbolTable& sym);

}
