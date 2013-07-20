#include "primitive_logic_types.h"

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

namespace fol{

ast_node ast_node(ast_node_type t):
    m_node(t){}

ast_node ast_node(ast_node_type t, ast_node *n):
    m_node(n | t){}

negated_formula negated_formula(ast_node *f):
    ast_node(NEGATED_FORMULA), m_formula(f){}

quantified_formula(ast_node_type t, ast_node *v, ast_node *f) :
    ast_node(t), m_variable(v), m_formula(f){}

connective connective(ast_node_type t, ast_node *l, ast_node *r) :
    ast_node(t), m_left_formula(l), m_right_formula(f){}

term term(ast_node* d, ast_node_type dt) :
    m_term(nullptr), m_end(this), ast_node(dt,d){}

term term(ast_node* d, ast_node_type dt, term** t, term** e):
    m_term(t), m_end(e), ast_node(dt, d){}

variable_descriptor variable_descriptor(std::string s) :
    ast_node(VARIABLE), name(s){}

constant_descriptor constant_descriptor(std::string s) :
    ast_node(CONSTANT), name(s){}

//  function and predicate descriptor have identical
//  ast_nodes - getType returns function and getDescriptor
//  returns nullptr

function_descriptor function_descriptor(std::string s, int a) :
    ast_node(FUNCTION), name(s), arity(a)
{}

predicate_descriptor predicate_descriptor(std::string s, int a) :
    ast_node(FUNCTION), name(s), arity(a)
{}

flat_term flat_term(ast_node* d) :
    ast_node(FUNCTION, d)
{}

int flat_term::length(){
    if(m_node->gettype() == FUNCTION) return m_node->getDescriptor()->arity;
    else return 0;
}

} // namespace fol
