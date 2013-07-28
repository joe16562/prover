#include <iostream>
#include <cstdint>
//#include "fol/primitive_logic_types.h"

#include "prover"

using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 1){
        cout << "Usage: prover problem.p" << endl;
        return 0;
    }

    prover proof_context(argv[1]);
    proof_context.given_clause();

    return 0;
}

