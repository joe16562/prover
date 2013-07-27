#include "parser.hpp"

using namespace fol;

SharedTermBank& shared_term_bank;
std::unordered_map<std::string,descritor*> constants;
std::unordered_map<std::string,descritor*> variables;
std::vector<ast_node*>& formulae;
std::istream& input;

parser::parser(SharedTermBank& shared_term_bank_, SymbolTable& variables_, SymbolTable& constants_,
               SymbolTable& functions_, SymbolTable& predicates_, LookupTable& arrities_, uintptr_t& next_id_,
               const char* problem_file)
    : shared_term_bank(shared_term_bank_), variables(variables_), constants(constants_),
      functions(functions_), predicates(predicates_), arrities(arrities_), next_id(next_id_)
{
    std::ifstream input_file;
    input_file.open(problem_file, std::ifstream::in);
    if(input_file.is_open() != true)
        exit();
    input = input_file;
}

void parse(){
    // id is unique per constant/variable/predicate/function prevously a
    // tagged pointer was used, but this has been replaced with an usnsigned
    // it, so the LSb's must be 0;
    next_id = 0;
    FormulaList* formulae;

}
