#include "parser.hpp"

using namespace fol;

SharedTermBank& shared_term_bank;
std::unordered_map<std::string,descritor*> constants;
std::unordered_map<std::string,descritor*> variables;
std::vector<ast_node*>& formulae;
std::istream& input;


parser::parser(SharedTermBank& shr, SymbolTable& vars, SymbolTable& cons,
           const char* problem_file)
    : shared_term_bank(shr), variables(vars), constants(cons){
    std::ifstream input_file;
    input_file.open(problem_file, std::ifstream::in);
    if(input_file.is_open() != true)
        exit();
    input = input_file;
}

void parse(){
    std::vector<child*> child_stack;
    std::vector<child
    //cin.sync_with_stdio(false);
    while (input){ // Check for errors/ end of file
        std::string nextLine;
        std::getString(is,nextLine);


    }

}
