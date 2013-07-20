%skeleton "lalr1.cc"
%require "2.7"

%defines
%define parser_class_name "fol_parser"

%code requires {
  #include <string>
  #include <vector>
  #include "primitive_logic_types.hpp"
  #include "../system/parser.hpp"

  using namespace fol;
}

/* define stack type */
%union {
    child* ast_node;
    std::string name;
    int arrity;
}

%parse-param { fol::parser& driver }
%lex-param   { fol::parser& driver }

/*
%locations
// The parsing context.

%initial-action
{
  // Initialize the initial location.
  @$.begin.filename = @$.end.filename = &driver.file;
};
*/

%debug
%error-verbose

/*  included in generated parser
    fol_grammar_driver.h defines the yylex, etc
    functions required by the parser
*/
%code {
  #include "parser.hpp"
  using namespace fol;

  std::vector<ast_node_*> global_term_stack;
}

/*
Tokens with semantic values
*/
%token <name> name
%token <arity> arity

/*
Tokens without semantic values
*/
%token negation '-'

/*
Types of semantic values for non terminals
*/
%type <ast_node> formula
%type <ast_node> predicate
%type <ast_node> function
%type <ast_node> term

%type <connective> connective
%type <quantifier> quantifier

%type <int> terms;

/*  dont delete non-pointer types  */
%destructor { delete[] $$; } <ast_node>
%destructor {  } name arity connective quantifier

%%

/*definitons must precede all formulas*/
input:
       /*  empty  */
    |  definition_list
    |  input formula	     { axioms.push_back($2);  }
    ;

defintion_list:
       /*  empty  */
    |  definition_list defintion
    ;

/*used to add names to the symbol tables*/
definition:
       "constant" '(' name ')'
       { driver.addConstant($3);
       }

    |  "variable" '(' name ')'
       { driver.addVariable($3);
       }

    |  "function"'(' name ',' arity ')'
       { driver.addFunction($3,$5));
       }

    |  "predicate" '(' name ',' arity ')'
       { driver.addPredicate($3,$5));
       }

    |  "goal" '(' formula ')'
       { driver.addGoal($3);
       }
    ;

formula:
       predicate
       { $$ = $1;
       }

    |  '(' formula connective formula ')'
       {
	 $$ = new connective_( $2, $3, $4 );
       }

    |  quantifer name formula
       { $$ = new quantifiedformula_($1, driver.getVariable($2), $3);
       }

    |  negation formula
       { $$ = new formula_($2);
       }

    /*eliminate trivial cases*/
    |  '(' formula ')'
    |  negation negation formula

    ;

/*
predicate:
       name  '('
       /* mid rule action */
       { predicates::iterator it = predicates.find($1);
	 if(it == predicates.end())
	   {/*error*/}
	 //  name and allocate term array
	 $$ = new predicate_($1, it->second);
	 //  add the term array to top of global stack
	 global_term_stack.push_back($$->terms);
       }
       terms ')'
    ;
    */

predicate:
       name  '('
       /* mid rule action */
       {
	 if(!driver.findPredicate(name))
	   {/*error*/}

	 //  name and allocate term array
	 $$ = new predicate_($1, it->second);
	 //  add the term array to top of global stack
	 global_term_stack.push_back($$->terms);
       }
       terms ')'
    ;

function:
       name '('
       /* mid rule action */
       { functions::iterator it = functions.find($1);
	 if(it == functions.end())
	   {/*error*/}
	 $$ = new function_($1,it->second);
	 global_term_stack.push_back($$->terms);
       }
       terms ')'
    ;

/* $$ is an index into the term array on the top of the
   global_term_stack vector - it allows arrays to be used
   directly in the structures instead of other conatianers
*/
terms:
       term
       { $$ = 1;
	 global_term_stack.back()[$$-1] = std::move(*$1);
       }

    |  terms ',' term
       { ++$$;
	 global_term_stack.back()[$$-1] = std::move(*$3);
       }

    ;

term:
       name
       { consants::iterator it = constants.find($1);
	 if(it != constants.end() ){
	   $$ = new variable_($1,nullptr,CONSTANT);
	 } else {
	 variables::iterator it = variables.find($1);
	 if(it != variables.end() ){
	   $$ = new term_($1,nullptr,VARIABLE);
	 }
	 }
       }

    |  function
       { $$ = $1;
       }
    ;

%%

int yylex (yy::fol_parser::semantic_type* yylval,
	   yy::fol_parser::location_type* yylloc)
{


}

/*
void yy::calcxx_parser::error (const yy::calcxx_parser::location_type& l,
		       const std::string& m)
{
driver.error (l, m);
}
*/
