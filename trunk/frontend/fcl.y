%{
#include <iostream>
#include <cmath>
#include "nodes.hpp"

extern int yylineno;
int yylex();

void yyerror(std::unique_ptr<ProgramNode>*, const char* s);
%}
%define parse.error verbose
%union {
    FireString string;
    int integer;
    ExpressionNode* expression;
    ParamListNode* params;
    CommandNode* command;
    CommandListNode* commandList;
    ThreadNode* thread;
    ThreadListNode* threadList;
    FireNode* fire;
    ProgramNode* program;
}

%token T_FIRE
%token T_LEFT
%token T_RIGHT
%token T_BEGIN
%token T_END
%token<string> T_IDENTIFIER
%token<string> T_STRING
%token<integer> T_INTEGER
%token T_END_CMD
%token T_SEPARATOR
%token T_THREAD
%token T_ERROR


%type <expression> expression
%type <params> params
%type <command> command func_call
%type <commandList> commands block
%type <thread> thread
%type <threadList> threads
%type <fire> fire
%type <program> program



%parse-param {std::unique_ptr<ProgramNode>* result}

%start program

%%

program:    threads fire                {
                                            result->reset( new ProgramNode($2,$1));
                                        }
threads:    threads thread              {
                                            $$ = $1;
                                            $$->add($2);
                                        }
            |                           {
                                            $$ = new ThreadListNode();
                                        }
block:      T_BEGIN commands T_END      {
                                            $$ = $2;
                                        }
thread:     T_THREAD T_STRING block     {
                                            $$ = new ThreadNode($3,$2.string, $2.length);
                                        }
fire:       T_FIRE block                {
                                            $$ = new FireNode($2);
                                        }
commands:   commands command            {
                                            $$ = $1;
                                            $$->add($2);
                                        }
            |                           {$$ = new CommandListNode();}
command:    func_call                   {
                                            $$ = $1;
                                        }
func_call:  T_IDENTIFIER T_LEFT params T_RIGHT T_END_CMD    {
                                                            $$ = new FuncCallNode($1.string, $1.length,$3);
                                                            }
params:     expression                  {
                                            $$ = new ParamListNode();
                                            $$->add($1);
                                         }
            |expression T_SEPARATOR params {
                                            $$ = $3;
                                            $$->add($1);
                                            }
            |                           {$$ = new ParamListNode();}
expression: T_STRING                    {$$ = new StringNode($1.string, $1.length);}
            |T_INTEGER                  {$$ = new IntegerNode($1);}
%%

void yyerror(std::unique_ptr<ProgramNode>* result, const char* s)
{
    std::cerr << yylineno << ": " << s << std::endl;
}

