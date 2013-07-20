#ifndef PRIMITIVE_LOGIC_TYPES_H
#define PRIMITIVE_LOGIC_TYPES_H

/**********************************************************
 *  Author:   Joseph Lawrie 16562@faith.sa.edu.au
 *  Date:     16 June 2013
 *  Modified: 20 July 2013
 *
 *  This file contains defintions for the basic
 *  structures used throughout the prover
 *
 *  A generic first order formula is represented by an
 *  abstract syntax tree of "child" objects. Each node is
 *  an array of child objects, which manage the use of a
 *  union - which may contain an enum and a pointer ORed
 *  together (be careful).
 *
 *********************************************************/

#include <cstdint>

/**********************************************************
 *  This namespace contains low level types and function
 *  for manipulating logical symbols, etc. It also avoids
 *  some clashes with std
 *********************************************************/

namespace fol{

struct child;

/**********************************************************
 *  A descriptor provides a unique reference to term/etc,
 *  while the other types only represent instances
 *********************************************************/

typedef formula child[1];
typedef predicate child[];
typedef function child[];
typedef quantified_formula child[2];
typedef connective child[2];
typedef constant child[1];
typedef variable child[1];

struct descriptor;

typedef union {
    child* chd;
    formula* frm;
    predicate* prd;
    quantified_formula* qf;
    connective* cnv;
    function* fun;
    constant* con;
    variable* var;
    descriptor* des;
} node_ptr;

/**********************************************************
 * Identifies the type of a node - that is, the type of the
 * node pointed to by that pointer
 *********************************************************/
enum node_type : uintptr_t{

    /******************************************************
     * The type must be known from two least significant
     * bits if it is one of constant, variable,function
     * or not
     *****************************************************/
    FUNCTION = 0,
    CONSTANT = 1,
    VARIABLE = 2,
    FORMULA = 3,
    SHARED_TERM_BANK_NODE = 3,

    NEGATED_FORMULA = (1 << 2) + FORMULA,
    PREDICATE       = (2 << 2) + FORMULA,
    CONNNECTIVE_OR  = (3 << 2) + FORMULA,
    CONNECTIVE_AND  = (4 << 2) + FORMULA,
    CONNECTIVE_IMP  = (5 << 2) + FORMULA,
    CONNECTIVE_IFF  = (6 << 2) + FORMULA,
    QUANTIFIER_UNI  = (7 << 2) + FORMULA,
    QUANTIFIER_EXI  = (8 << 2) + FORMULA,
    EQUATIONAL_LIT_POS  = (9 << 2) + FORMULA,
    EQUATIONAL_LIT_NEG  = (10 << 2) + FORMULA

};
const uintptr_t FORMULA_MASK = 0x3;

/**********************************************************
 *  A wrapper around node_ptr to allow for simpler use
 *  and management
 *********************************************************/
struct child {
    node_ptr child_ptr;
    inline node_type getType();
    inline void setType(node_type t);
    inline node_ptr getPointer();
    inline uint getArrity();
};

/**********************************************************
 *  Only one per a symbol, etc - not important during
 *  the actual proving, so generated symbols (Skolem
 *  constant/functions) need only be pointers
 *********************************************************/
struct descriptor {
    std::string name;
    uint arrity;

    descriptor(std::string& s);
    descriptor(std::string& s, int i);
};

child* new_function(descriptor* d, int i, child** c );
child* new_function(descriptor* d, child** c );

child* new_predicate(descriptor* d, child** c );
child* new_predicate(descriptor* d, int i, child** c );

child* new_constant(descriptor* d);
child* new_variable(descriptor* d);

child* new_negated_formula(child* f);
child* new_predicate();
child* new_connective(child* f, node_type t,child* f);
child* new_quantified(node_type t, descriptor* d, child* f);
child* new_equational_lit(child* lt, node_type t, child* rt);

}//END Namesplace fol

#include "primitive_logic_types_inl.h"

#endif // PRIMITIVE_LOGIC_TYPES_H
