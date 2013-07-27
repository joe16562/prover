#include "shared_term_bank.h"

#include <assert.h>

/*********************************************************
 *  Author:   Joseph Lawrie
 *  Date:     16 June 2013
 *
 *  Implementation of SharedTermBank
 *
 *  This structure is similar to a symbol table. The
 *  insertion process determines if a term already exists,
 *  and then returns a pointer to that term to be used by
 *  other terms.
 *
 *  Important: Every child* inserted into the
 *  unordered_map of a SharedTermBankNode MUST have all of
 *  its subterms replaced by unique descriptors
 *
 ********************************************************/

namespace fol{

/**********************************************************
 *  TermHasher and TermEqualityPredicate are simple
 *  functors used as parameters of the stl unordered_map
 *  container - the unordered maps are used to search
 *  with different argument lists
 *********************************************************/

class TermHasher{
    size_t operator() (child* child_to_be_hashed){
        if( (child_to_be_hashed->getType == FUNCTION) ||
                (child_to_be_hashed->getType == PREDICATE)){
        return MurmurHash3_x64_64(child_to_be_hashed,
                                  sizeof(child) * (child_to_be_hashed->getArrity() + 1));
        }
        return MurmurHash3_x64_64(child_to_be_hashed);
    }
};

class TermEqualityPredicate{
    bool operator() (child* a, child* b){
        if(a->getType() != b->getType())
            return false;
        if( (a->getType == FUNCTION) || (a->getType == PREDICATE))
            for(int i = 0; i < a[1].getArrity(); i++)
                if(a[i] != b[i]) return false;
        return true;
    }
};

SharedTermBank::SharedTermBank()
{
}

/**********************************************************
 *  Memory is curerently not managed because the term bank
 *  exists for the length of the program, and no deletions
 *  of terms are currently implemented.
 *
 *  If this changes, it will be managed through the use
 *  of shared pointers from the stl so this destructor
 *  will still be blank.
 *********************************************************/

SharedTermBank::~SharedTermBank()
{

}

/**********************************************************
 *  Returns a valid (no strings attached) pointer to a
 *  function,etc (type of term), which is identical to if
 *  it had been created without the bank
 *********************************************************/
child* SharedTermBank::insert(child* term){

    if(t == nullptr) return nullptr;

    // Check if this term is already known
    if(lookup_table.find(term) != lookup_table.end())
        return term;

    switch(term->getType()){

    case FUNCTION:
        // Insert subterms, replacing them with the shared term
        for(auto it = &term[2]; it != term[1].getArrity(); it++ )
            term[it] = insert(term[it]);
        //FALL THROUGH

    case CONSTANT:
    case VARIABLE:
    { // Prevent skipped intialization of it
        auto it = lookup_table.insert(term);
        if(it->second == false){ // A shared term already exists
            delete[] term; //(non recursive - subterms are all in lookup_table)
            return *(it->first); //return the shared copy
        }
        else // Term has been inserted
            return term;
    }
        break;

    default:
        assert(term->getType() == FUNCTION
               || term->getType() == VARIABLE
               || term->getType() == CONSTANT);
        break;
    }
}

}
