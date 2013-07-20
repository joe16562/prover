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

    prover proof(argv[1]);
    proof.given_clause();

    return 0;
}

