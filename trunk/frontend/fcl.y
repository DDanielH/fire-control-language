%{
#include <iostream>
#include <cmath>
#include "nodes.hpp"

int yylex();

void yyerror(std::unique_ptr<ExprNode>*, const char* s);
%}

%union {
    double value;
    ExprNode* node;
}

%token<value> T_DECIMAL
%token T_PLUS
%token T_MINUS
%token T_TIMES
%token T_DIVIDE
%token T_OPEN
%token T_CLOSE
%token T_COMMA
%token T_SIN
%token T_COS
%token T_MAX
%token T_ERROR

%left T_PLUS T_MINUS
%left T_TIMES T_DIVIDE

%type <node> expr

%parse-param {std::unique_ptr<ExprNode>* result}

%start value

%%

value: expr                 { result->reset($1); }
expr: T_DECIMAL             { $$ = new ValueNode($1); }
    | T_OPEN expr T_CLOSE   { $$ = $2; }
    | expr T_PLUS expr      { $$ = new BinaryOpNode($1, $3, OP_PLUS); }
    | expr T_MINUS expr     { $$ = new BinaryOpNode($1, $3, OP_MINUS); }
    | expr T_TIMES expr     { $$ = new BinaryOpNode($1, $3, OP_TIMES); }
    | expr T_DIVIDE expr    { $$ = new BinaryOpNode($1, $3, OP_DIVIDE); }
    | T_SIN T_OPEN expr T_CLOSE { $$ = new SinNode($3); }
    | T_COS T_OPEN expr T_CLOSE { $$ = new CosNode($3); }
    | T_MAX T_OPEN expr T_COMMA expr T_CLOSE { $$ = new MaxNode($3, $5); }

%%

void yyerror(std::unique_ptr<ExprNode>* result, const char* s)
{
    std::cerr << s << std::endl;
}

