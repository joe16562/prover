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
#include <vector> //for defintion of FormulaList

/**********************************************************
 *  This namespace contains low level types and function
 *  for manipulating logical symbols, etc. It also avoids
 *  some clashes with std
 *********************************************************/

namespace fol{

struct child;

/**********************************************************
 *  The basic types are represented by these arrays - the
 *  type of a node is determined from the first child in
 *  the array - similar to inheritance, but allows for
 *  compact representation of terms, etc which have a
 *  variable length - (so it avoids an extra layer of
 *  pointer indirection and confusion, but its still not
 *  ideal)
 *********************************************************/

typedef child formula[2];             // Type, Formula
typedef child quantified_formula[3];  // Type, Variable, Formula
typedef child connective[3];          // Type, Formula, Formula
typedef child equational_lit[3];      // Type, Id, Id
typedef child constant[1];            // Type/Id
typedef child variable[1];            // Type/Id
typedef child* predicate;             // Type/Id, Arrity, Terms
typedef child* function;              // Type/Id, Arrity, Terms

/**********************************************************
 *  A descriptor provides a unique reference to term/etc,
 *  while the other types only represent instances
 *********************************************************/

//struct descriptor;
typedef uintptr_t descriptor;

typedef union {
    child* chd;
    /*
    formula* frm;
    predicate* prd;
    quantified_formula* qf;
    connective* cnv;
    function* fun;
    constant* con;
    variable* var;
    descriptor* des;
    */
} node_ptr;

/**********************************************************
 * Identifies the type of a node - that is, the type of the
 * node which owns the pointer
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

    NEGATED_FORMULA = (1 << 2) + FORMULA,
    PREDICATE       = (2 << 2) + FORMULA,
    CONNECTIVE_OR  = (3 << 2) + FORMULA,
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
    child* next;

    inline node_type getType(){
        node_type t = ((uintptr_t)next) & FORMULA;
        return (t != 3) ? t : (node_type)next;
    }

    inline void setType(node_type t);

    inline child* getSubFormula(){
        return next;}

    inline child* getSubTerm(){
        return (child*)
                (((uintptr_t)next) & ~FORMULA_MASK);}

    inline uintptr_t getDescriptor(){
        return (((uintptr_t)next) & ~FORMULA_MASK);}

    inline uintptr_t setDescriptor(uintptr_t id){
        next = (((uintptr_t)next) & FORMULA_MASK) | id;}

    inline uintptr_t getArrity(){
            return (uintptr_t)next;}

};

child* new_function(const descriptor* d, unsigned int i, const child** c );
child* new_function(const descriptor* d, const child** c );

child* new_predicate(const descriptor* d, const child** c );
child* new_predicate(const descriptor* d, unsigned int i, const child** c );

child* new_constant(const descriptor* d);
child* new_variable(const descriptor* d);

child* new_negated_formula(const child* f);
child* new_connective(const child* f, node_type t,const child* f);
child* new_quantified(node_type t, const descriptor* d, const child* f);
child* new_equational_lit(const child* lt, node_type t, const child* rt);

typedef std::vector<child*> FormulaList;

}//END Namesplace fol

#include "primitive_logic_types_inl.h"

#endif // PRIMITIVE_LOGIC_TYPES_H
