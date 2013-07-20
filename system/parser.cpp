#include "parser.hpp"

using namespace fol;

SharedTermBank& shared_term_bank;
std::unordered_map<std::string,descritor*> constants;
std::unordered_map<std::string,descritor*> variables;
std::vector<ast_node*>& formulae;
std::istream& input;


parser::parser(SharedTermBank& shr, SymbolTable& sym, std::vector<ast_node*>& frm,
           const char* problem_file){
}
void parse(){

}
