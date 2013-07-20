#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "primitive_logic_types.h"
#include "../murmurhash/murmurhash.hpp"

#include <memory>

namespace fol{

// added 64 bit hash by xor folding 128 bit hash
#define MURMUR_SEED 42
uint64_t MurmurHash3_x64_64 (const void * key, const int len)
{
    uint64_t out[2];
    MurmurHash3_x64_128 ( key, len, MURMUR_SEED, (void*) out );
    return out[0] ^ out[1];
}

enum traversal_enum{
    FIRST,
    LAST
};

template<typename f>
for_each_node(ast_node* r){
    switch (r.getType()){
    case FUNCTION:
    case PREDICATE:
        f(r, FIRST);
        for(auto it = ((term*)r).begin(); it != ((term*)r).end(); it++){
            for_each_node<f>(*it);
        }
        f(r, LAST);
        break;
    case CONSTANT:
    case VARIABLE:
        f(r, FIRST);
        f(r, LAST);
        break;

    case NEGATED_FORMULA:
        f(r, FIRST);
        for_each_node<f>( ((negated_formula*)r).m_formula);
        f(r, LAST);
        break;

    case CONNNECTIVE_OR:
    case CONNECTIVE_AND:
    case CONNECTIVE_IMP:
    case CONNECTIVE_IFF:
        f(r, FIRST);
        for_each_node<f>( ((connective*)r).m_left_formula);
        for_each_node<f>( ((connective*)r).m_right_formula);
        f(r, LAST);
        break;

    case QUANTIFIER_UNI:
    case QUANTIFIER_EXI:
        f(r, FIRST);
        for_each_node<f>( ((connective*)r).m_left_formula);
        for_each_node<f>( ((connective*)r).m_right_formula);
        f(r, LAST);
        break;

    case EQUATIONAL_LIT:
        f(r, FIRST);
        for_each_node<f>( ((equational_literal*)r).m_left_term);
        for_each_node<f>( ((equational_literal*)r).m_right_term);
        f(r, LAST);
        break;

    default:
        break;
    }
}

} //fol

#endif // UTILITIES_HPP
