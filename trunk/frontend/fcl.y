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

%token T_FIRE
%token T_LEFT
%token T_RIGHT
%token T_BEGIN
%token T_END
%token T_IDENTIFIER
%token T_STRING
%token T_INTEGER
%token T_NEWLINE
%token T_END_CMD
%token T_SEPARATOR
%token T_THREAD
%token T_ERROR


%type <node> expr

%parse-param {std::unique_ptr<ExprNode>* result}

%start program

%%

program:    threads fire                { }
threads:    threads thread              { }
            |                           {}
block:      T_BEGIN commands T_END      {}
thread:     T_THREAD T_STRING block     {}
fire:       T_FIRE block                {}
commands:   commands command            {}
            |                           {}
command:    func_call                   {}
func_call:  T_IDENTIFIER T_LEFT params T_RIGHT T_END_CMD    {}
params:     expression                  {}
            |expression T_SEPARATOR params {}
            |                           {}
expression: T_STRING                    {}
            |T_INTEGER                  {}
%%

void yyerror(std::unique_ptr<ExprNode>* result, const char* s)
{
    std::cerr << s << std::endl;
}

