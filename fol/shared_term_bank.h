#ifndef SHARED_TERM_BANK_H
#define SHARED_TERM_BANK_H

/***********************************************************
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
 *  Notes: This structure is used ONLY to ORGANISE the
 *  sharing of term nodes (functions and predicates,etc)
 *  It returns completely valid syntax trees, EXCEPT that
 *  term pointers may point to the same node as other term
 *  pointers - this is what is meant by 'sharing'
 *
 *  The memory management of the new pointer is the
 *  responsibility of this structure.
 *
 **********************************************************/

#include <unordered_map>

#include "primitive_logic_types.h"
#include "utilities.hpp"

namespace fol{

class TermHasher;
class TermEqualityPredicate;

class SharedTermBank
{
    // Could be another container - rehashing is a performance problem
    // but so is lookup
    std::unordered_map<child*, child*, TermHasher, TermEqualityPredicate> lookup_table;

public:
    //  Careful! Don't delete 'term'
    //  after inserting it
    descriptor* insert(child* term);
    descriptor* search(child* term);

    SharedTermBank();
    ~SharedTermBank();

};

}
#endif // SHARED_TERM_BANK_H
