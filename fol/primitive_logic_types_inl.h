#ifndef PRIMITIVE_LOGIC_TYPES_INL_H
#define PRIMITIVE_LOGIC_TYPES_INL_H

/*********************************************************
 *  Author:   Joseph Lawrie 16562@faith.sa.edu.au
 *  Date:     16 June 2013
 *
 *  This file contains defintions for inline
 *  functions that operate on basic logic types
 *
 ***********************************************/

#include "primitive_logic_types.h"

inline ast_node_type node_type::getType()
{
    uintptr_t t = static_cast<uintptr_t>(m_node) & FORMULA_MASK;
    return t == FORMULA ? m_node : t;
}

inline ast_node* node_type::getNode(){
    return static_cast<uintptr_t>(m_node) & ~FORMULA_MASK;
}

#endif // PRIMITIVE_LOGIC_TYPES_INL_H
