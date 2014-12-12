    /* Macros */
%{
#include "nodes.hpp"
#include "fcl.parser.hh"

#include <cstdlib>
#include <iostream>
%}


DIGIT [0-9]

%option noyywrap

%%
    /* Rules */

{DIGIT}+(\.{DIGIT}*)?   { yylval.value = std::atof(yytext); return T_DECIMAL; }

"+"                 { return T_PLUS; }
"-"                 { return T_MINUS; }
"*"                 { return T_TIMES; }
"/"                 { return T_DIVIDE; }

"("                 { return T_OPEN; }
")"                 { return T_CLOSE; }
","                 { return T_COMMA; }

"sin"               { return T_SIN; }
"cos"               { return T_COS; }
"max"               { return T_MAX; }

.                   { std::cerr << "ERROR" << std::endl; return T_ERROR; }

%%
    /* Procedures */
