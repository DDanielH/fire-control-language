%{
#include <iostream>
#include <cmath>
#include "nodes.hpp"

extern int yylineno;
int yylex();

void yyerror(std::unique_ptr<ProgramNode>*, const char* s);
%}

%union {
    FireString string;
    int integer;
    ExpressionNode* expression;
    ParamListNode* params;
    CommandNode* command;
    CommandListNode* commandList;
    ThreadNode* thread;
    ThreadListNode* threadList;
    ClientNode* client;
    ClientListNode* clientList;
    FireNode* fire;
    ProgramNode* program;
    FuncCallNode* funcCall;
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
%token T_VAR
%token T_ASSIGN
%token T_CLIENT
%token T_FOR
%token T_IN

%type <expression> expression
%type <params> params
%type <command> command var_decl foreach
%type <commandList> commands block
%type <thread> thread
%type <threadList> threads
%type <fire> fire
%type <program> program
%type <client> client
%type <clientList> clients
%type <funcCall> func_call

%define parse.error verbose
%parse-param {std::unique_ptr<ProgramNode>* result}

%start program

%%

program:    threads clients fire        { result->reset(new ProgramNode($3, $1, $2)); }

threads:    threads thread              { $$ = $1; $$->add($2); }
            |                           { $$ = new ThreadListNode(); }
thread:     T_THREAD T_STRING block     { $$ = new ThreadNode($3, $2.string, $2.length); }

clients:    clients client              { $$ = $1; $$->add($2); }
            |                           { $$ = new ClientListNode(); }
client:     T_CLIENT T_STRING block     { $$ = new ClientNode($3, $2.string, $2.length); }

fire:       T_FIRE block                { $$ = new FireNode($2); }
block:      T_BEGIN commands T_END      { $$ = $2; }

commands:   commands command            { $$ = $1; $$->add($2); }
            |                           { $$ = new CommandListNode(); }
command:    var_decl                    { $$ = $1; }
            | foreach                   { $$ = $1; }
            | func_call T_END_CMD       { $$ = new FuncCallCommandNode($1); }

var_decl:   T_VAR T_IDENTIFIER T_ASSIGN expression T_END_CMD
                                        { $$ = new VarDeclarationNode($2.string, $2.length,$4); }
foreach:    T_FOR T_LEFT T_IDENTIFIER T_IN T_IDENTIFIER T_RIGHT block
                                        { $$ = new ForeachNode($7,$5.string, $5.length,$3.string, $3.length); }

func_call:  T_IDENTIFIER T_LEFT params T_RIGHT
                                        { $$ = new FuncCallNode($1.string, $1.length,$3); }
params:     expression                  { $$ = new ParamListNode(); $$->add($1); }
            | expression T_SEPARATOR params
                                        { $$ = $3; $$->add($1); }
            |                           { $$ = new ParamListNode(); }

expression: T_STRING                    { $$ = new StringNode($1.string, $1.length); }
            | T_INTEGER                 { $$ = new IntegerNode($1); }
            | T_IDENTIFIER              { $$ = new IdentifierNode($1.string, $1.length); }
            | func_call                 { $$ = $1; }
%%

void yyerror(std::unique_ptr<ProgramNode>* result, const char* message)
{
    std::cerr << yylineno << ": " << message << std::endl;
}

