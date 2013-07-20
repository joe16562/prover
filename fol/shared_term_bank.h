#ifndef SHARED_TERM_BANK_H
#define SHARED_TERM_BANK_H

/*********************************************************
 *  Author:   Joseph Lawrie
 *  Date:     16 June 2013
 *
 *  This class implements a perfectly shared
 *  term bank, with the purpose of reducing
 *  redundant memory usage when storing large
 *  numbers of similar terms.
 *
 *  The pointer to a syntax tree representing a
 *  term is added to the bank using the insert
 *  function, and a pointer to the new term is
 *  returned.
 *
 *  Similar structures are found in the provers
 *  Vampire and E
 *
 *
 *  Notes: Every term returned by the term bank is either a
 *  pointer to a shared term or an array of such pointers
 *  (other terms may be abstract syntax trees)
 *
 ***********************************************/

#include "primitive_logic_types.h"
#include "utilities.hpp"

#include <map>

namespace fol{

class SharedTermBank
{
    std::map<ast_node*, ast_node*> termTree;

public:
    ast_node* insert(term*);
    ast_node* search(term*);

    SharedTermBank();
    ~SharedTermBank();

};

}
#endif // SHARED_TERM_BANK_H
