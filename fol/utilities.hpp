#ifndef UTILITIES_HPP
#define UTILITIES_HPP

/**********************************************************
 *  Author:   Joseph Lawrie 16562@faith.sa.edu.au
 *
 *  Contains a number of useful functions, in particular
 *  the murmurhash function and a number of templates
 *  for traversing asts
 *
 *********************************************************/

#include "primitive_logic_types.h"
#include "../murmurhash/murmurhash.hpp"

#include <memory>

namespace fol{

// added 64 bit hash by xor folding 128 bit hash
#define MURMUR_SEED 42
inline uint64_t MurmurHash3_x64_64 (const void * key, const int len)
{
    uint64_t out[2];
    MurmurHash3_x64_128 ( key, len, MURMUR_SEED, (void*) out );
    return out[0] ^ out[1];
}

enum traversal_enum{
    FIRST,
    MIDDLE,
    LAST
};

template<typename f>
void for_each_node(child* r){ //pointer to the node
    switch (r->getType()){
    case FUNCTION:
    case PREDICATE:
    {
        auto terms = r->getSubTermArray();
        auto arrity = r->getArrity();
        f(r, FIRST);
        for(child* it = terms; it != terms + arrity; it++){
            for_each_node<f>(it);
        }
        f(r, LAST);
    }
        break;
    case CONSTANT:
    case VARIABLE:
        f(r, FIRST);
        f(r, LAST);
        break;

    case NEGATED_FORMULA:
        f(r, FIRST);
        for_each_node<f>(r->getNegatedFormula());
        f(r, LAST);
        break;

    case CONNECTIVE_OR:
    case CONNECTIVE_AND:
    case CONNECTIVE_IMP:
    case CONNECTIVE_IFF:
        f(r, FIRST);
        for_each_node<f>(r->getLeftSubFormula());
        for_each_node<f>(r->getRightSubFormula());
        f(r, LAST);
        break;

    case QUANTIFIER_UNI:
    case QUANTIFIER_EXI:
        f(r, FIRST);
        for_each_node<f>(r->getBoundVariable());
        for_each_node<f>(r->getBoundFormula);
        f(r, LAST);
        break;

    case EQUATIONAL_LIT_POS:
    case EQUATIONAL_LIT_NEG:
        f(r, FIRST);
        for_each_node<f>(r->getLeftSubTerm());
        for_each_node<f>(r->getRightSubTerm());
        f(r, LAST);
        break;

    default:
        break;
    }
}

template<typename f>
void for_each_sub_formula(child* r){ //pointer to the node
    switch (r->getType()){
    case PREDICATE:
        f(r, FIRST);
        f(r, LAST);
        break;

    case NEGATED_FORMULA:
        f(r, FIRST);
        for_each_sub_formula<f>(r->getNegatedFormula());
        f(r, LAST);
        break;

    case CONNECTIVE_OR:
    case CONNECTIVE_AND:
    case CONNECTIVE_IMP:
    case CONNECTIVE_IFF:
        f(r, FIRST);
        for_each_sub_formula<f>(r->getLeftSubFormula());
        for_each_sub_formula<f>(r->getRightSubFormula());
        f(r, LAST);
        break;

    case QUANTIFIER_UNI:
    case QUANTIFIER_EXI:
        f(r, FIRST);
        for_each_sub_formula<f>(r->getBoundFormula);
        f(r, LAST);
        break;

    case EQUATIONAL_LIT_POS:
    case EQUATIONAL_LIT_NEG:
        f(r, FIRST);
        f(r, LAST);
        break;

    case CONSTANT:
    case VARIABLE:
    case FUNCTION:
        /*error*/
        break;

    default:
        break;
    }
}

template<typename f>
void for_each_sub_term(child* r){ //pointer to the node
    switch (r->getType()){
    case FUNCTION:
    {
        auto terms = r->getSubTermArray();
        auto arrity = r->getArrity();
        f(r, FIRST);
        for(child* it = terms; it != terms + arrity; it++){
            for_each_sub_term<f>(it);
        }
        f(r, LAST);
    }
        break;

    case PREDICATE:
    {
        auto terms = r->getSubTermArray();
        auto arrity = r->getArrity();
        for(child* it = terms; it != terms + arrity; it++){
            for_each_sub_term<f>(it);
        }
    }
        break;

    case CONSTANT:
    case VARIABLE:
        f(r, FIRST);
        f(r, LAST);
        break;

    case NEGATED_FORMULA:
        for_each_sub_term<f>(r->getNegatedFormula());
        break;

    case CONNECTIVE_OR:
    case CONNECTIVE_AND:
    case CONNECTIVE_IMP:
    case CONNECTIVE_IFF:
        for_each_sub_term<f>(r->getLeftSubFormula());
        for_each_sub_term<f>(r->getRightSubFormula());
        f(r, LAST);
        break;

    case QUANTIFIER_UNI:
    case QUANTIFIER_EXI:
        for_each_sub_term<f>(r->getBoundVariable());
        for_each_sub_term<f>(r->getBoundFormula);
        break;

    case EQUATIONAL_LIT_POS:
    case EQUATIONAL_LIT_NEG:
        for_each_sub_term<f>(r->getLeftSubTerm());
        for_each_sub_term<f>(r->getRightSubTerm());
        f(r, LAST);
        break;

    default:
        break;
    }
}

} //fol

#endif // UTILITIES_HPP
