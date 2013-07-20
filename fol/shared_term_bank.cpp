#include "shared_term_bank.h"

namespace fol{

//  Used to insert a term into shared memory bank using
//  the template function for_each_node in utilities.hpp

class inserter{
    SharedTermBank& shr;
    SymbolTable& sym;
public:
    inserter(SharedTermBank& shr, SymbolTable& sym);

    void operator()(ast_node* n, traversal_enum t){
        if(t == FIRST) return;

        switch (n->gettype()){
        case CONSTANT:
        case VARIABLE:
            sym.insert(n);
        case FUNCTION:
            shr.insert(n);
        default:
            break;
        }
    }


};

SharedTermBank::SharedTermBank()
{
}

/*  This function takes a pointer a term represented by
 *  its abstract syntax tree, then systematic flattens the
 *  terms from the bottom, returning a pointer to the term's
 *  representation in the shared term bank
 */
term* SharedTermBank::insert(term* t){

    if(t == nullptr) return nullptr;

    /*  Insert all subterms of *t - then insert *t itself.
     *  The loop therefore operates on temrinal nodes first,
     *  so we can replace each non terminal node term( term1(subterms), ... termN)
     *  with the compact representation term( term*1,nullptr,.. term*N, nullptr);
     */

    /*  Guarenteed flat term representation now ie
     *  *t = term_desxcriptor, pointer to end, term pointers...
     */

}

}
