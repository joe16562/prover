#include "clausification.hpp"
#include <cassert>

/**********************************************************
 *  This file implements the conversion of a set of
 *  formulaes to an equisatisfiable set of clauses thorugh
 *  the function ConvertToCnf();
 *********************************************************/

namespace fol {

typedef std::unordered_set<child*> VariableSet;

/**********************************************************
 *  Copies an ast, used during conversion to cnf, all terms
 *  have been replaced by descriptors at this point
 *********************************************************/

child* copy(const child* child_to_copy){
    switch(child_to_copy->getType()){
    case NEGATED_FORMULA: //recursive copy of subtree
        return new_negated_formula(
                    copy(child_to_copy->getNegatedFormula()));
        break;

    case PREDICATE: //non-recursive copy because of shared terms
        return new_predicate(
                    child_to_copy->getDescriptor(),
                    child_to_copy->getArrity(),
                    child_to_copy->getSubTermArray());
        break;

    case CONNECTIVE_OR: //recursive copy of subtrees
    case CONNECTIVE_AND:
    case CONNECTIVE_IFF:
    case CONNECTIVE_IMP:
        return new_connective(
                    copy(child_to_copy->getLeftSubFormula()),
                    child_to_copy->getType(),
                    copy(child_to_copy->getSubRightFormula())
                );
        break;

    case QUANTIFIER_EXI:
    case QUANTIFIER_UNI:
        return new_quantified(
                    child_to_copy->getType(),
                    child_to_copy->getBoundVariable(),
                    copy(child_to_copy->getBoundFormula())
                );
        break;

    case EQUATIONAL_LIT_NEG:
    case EQUATIONAL_LIT_POS:
        return new_equational_lit(
                    child_to_copy->getLeftSubTerm(),
                    child_to_copy->getRightSubTerm()
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

/**********************************************************
 *  Standardise a formula during conversion to clause
 *  normal form - deals with shared term structure
 *********************************************************/

struct FormulaStandardiser{

    std::stack<child*> standardised_terms_;
    VariableSet& bound_variables_;
    Prover& proof_context_;
    SubstitutionList& substitutions_;

    FormulaStandardiser(Prover& proof_context,SubstitutionList& substitutions,
                        VariableSet& bound_variables):
        standardised_terms_(), bound_variables_(bound_variables),
        proof_context_(proof_context), substitutions_(substitutions){

    }

    void operator()(child* f, traversal_enum t){
        if(t != LAST)
            return;
        switch(formula->getType())
        {
        case VARIABLE: //every variable should be bound
            if(bound_variables_.insert(f).second()){
                // inserted, new variable
                standardised_terms_.push(f);
            } else {
                // inserted, old variable
                auto sub = substitutions_[f];
                if(sub == nullptr) // used once
                    sub = proof_context_.GetNextTermId();
                standardised_terms_.push(sub);
            }
            break;

        /* Here we create a new copy of the function node,
         * replace its subterms and then add it to the
         * shared term bank, before placing back on the stack
         * to be used by subsequent standardisation
         */
        case FUNCTION:
            {
            auto arrity = f->getArrity();
            auto terms = f->getSubTermArray();
            child* new_function = new_function(f->getDescriptor(),arrity,terms);
            /* warning - working backwards, popping from stack */
            auto new_terms = new_function->getSubTermArray();

            for(auto it = new_terms + arrity; it != new_terms; --it){
                //subterms have already been standardised
                *it = standardised_terms_.pop();
            }
            proof_context_.insert(new_function);
            standardised_terms_.push(new_function);
            }
            break;

        /* Predicates are not shared, so we can safely copy in the
         * new subterms
         */
        case PREDICATE:
            {
            // replace subterms with their standardised versions
            auto arrity = f->getArrity();
            auto terms = f->getSubTermArray();
            for(auto it = terms + arrity; it != terms; --it){
                //subterms have already been standardised
                *it = standardised_terms_.pop();
            }
            }
            break;

        /* Do for equality literals as we do for predicates */
        case EQUATIONAL_LIT_NEG:
        case EQUATIONAL_LIT_POS:
            f->getRightSubTerm() = standardised_terms_.pop();
            f->getLeftSubTerm() = standardised_terms_.pop();
            break;

        default:
            break;
        }
    }
};

FormulaList* StandardiseFormulaList(Prover& proof_context, FormulaList*
                                    formulae, SubstitutionList& substitutions){
    VariableSet bound_variables;
    for(auto it = formulae->begin(); it != formulae->end(); it++)
    {
        // Create the functor which will standardise each formula
        FormulaStandardiser standardiser(proof_context, formulae,
                                         substitutions, bound_variables);
        for_each_sub_term<standardiser(*it);
    }
    return formulae;
}
