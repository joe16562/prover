#ifndef PRIMITIVE_LOGIC_TYPES_H
#define PRIMITIVE_LOGIC_TYPES_H

/**********************************************************
 *  Author:   Joseph Lawrie 16562@faith.sa.edu.au
 *  Date:     16 June 2013
 *
 *  This file contains defintions for the basic
 *  structures used throughout the prover
 *
 *  A generic formula is represented by an
 *  abstract syntax tree. Each node inherits from
 *  node_type, which encodes the type of node and
 *  a descriptor of the node for term nodes
 *
 *********************************************************/

#include <cstdint>

namespace fol{

struct formula;
struct predicate;
struct term;
struct function;
struct variable;
struct constant;

/**********************************************************
 *  A descriptor provides a unique reference to term/etc,
 *  while the other types only represent instances
 *********************************************************/
struct descriptor;
struct term_descriptor;

/**********************************************************
 * Identifies the type of a node
 *********************************************************/
enum ast_node_type : uinttpr_t{

    /******************************************************
     * The type must be known from two least significant
     * bits if it is one of constant, variable,function
     * or not
     *****************************************************/
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

};
const uintptr_t FORMULA_MASK = 0x3;

/**********************************************************
 *  ast_node is inherited by all possible nodes, even those
 *  without children. The struct simply stores a pointer,
 *  and uses this pointer to identify the type of the
 *  inheriting class
 *
 *  In the case of terms, this pointer also stores the
 *  address of a descriptor struct, which identifies a
 *  unique function,predicate, constant or varaible.
 *
 *  The type is obtained via a call to
 *  getType(), and the address of the descriptor is obtained
 *  by getNode().
 *
 *  The use of a full pointer to store the type in the
 *  case of a formula is not important, as padding/overhead
 *  will likely prevent any improvement
 *********************************************************/
struct ast_node{
    inline ast_node_type getType();
    inline ast_node* getNode();

    //constructors
    ast_node(ast_node_type t);
    ast_node(ast_node_type t, ast_node* n);
private:
    //storage of the descriptor is shared with the
    //descriptor's type
    ast_node* m_node;
};

struct negated_formula : ast_node{
    ast_node* m_formula;
    negated_formula(ast_node* f);
};

struct quantified_formula : ast_node{
    ast_node* m_variable;
    ast_node* m_formula;
    quantified_formula(ast_node_type t, ast_node* v, ast_node* f);
};

struct connective : ast_node{
    ast_node* m_left_formula;
    ast_node* m_right_formula;
    connective(ast_node_type t, ast_node* l, ast_node* r);
};

struct equational_literal : ast_node{
    ast_node* m_left_term;
    ast_node* m_right_term;
    equational_literal(ast_node_type t, ast_node* l, ast_node* r);
};

//  Note: A predicate is implemented as a term that
//  appears where a subformula usually would

/**********************************************************
 *  Any term is represented by an array of these
 *  structs. The end() pointers are used like STL end
 *  iterators
 *********************************************************/
struct term : ast_node{
    term** m_term;
    term** m_end;

    //inline term* next(){return this + 1;}
    inline term** begin(){return m_term;}
    inline term** end(){return m_end;}
    inline term* child(int n){return m_end != this ? m_term[n] : nullptr;}

    term(ast_node* d); //create term from descriptor
    term(ast_node* d, term** t, term** e); //create term from subterms
};

/**********************************************************
 *  A descriptor of a variable
 **********************************************************/
struct variable_descriptor : ast_node{
    std::string name;
    variable_descriptor(std::string s);
};

/**********************************************************
 *  A descriptor of a constant
 **********************************************************/
struct constant_descriptor : ast_node{
    std::string name;
    constant_descriptor(std::string s);
};

/**********************************************************
 *  A descriptor of a function
 **********************************************************/
struct function_descriptor : ast_node{
    std::string name;
    int arity;
    function_descriptor(std::string s, int a);
};

/**********************************************************
 *  A descriptor of a predicate
 **********************************************************/
struct predicate_descriptor : ast_node{
    std::string name;
    int arity;
    predicate_descriptor(std::string s, int a);
};

/**********************************************************
 *  A linear representation of a term, used as the key in
 *  shared term datastructure shared_term_bank.hpp
 **********************************************************/
struct flat_term : ast_node{
    int length();
    inline ast_node* begin(){ return (ast_node*)(this + 1);}
    flat_term();
};

}//END Namesplace fol

#include "primitive_logic_types_inl.h"

#endif // PRIMITIVE_LOGIC_TYPES_H
