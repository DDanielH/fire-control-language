    /* Macros */
%{
#include "nodes.hpp"
#include "fcl.parser.hh"

#include <cstdlib>
#include <iostream>
%}

%option noyywrap

%%
    /* Rules */

"fire"             { return T_FIRE;}
"thread"           { return T_THREAD;}
"("                { return T_LEFT;}
")"                { return T_RIGHT;}
"{"                { return T_BEGIN;}
"}"                { return T_END;}
\"[^\"]*\"         {
                      yylval.string = yytext;
                      return T_STRING;
                   }
[0-9]+             {
                      yylval.integer = atoi(yytext);
                      return T_INTEGER;
                   }
\n                 { yylineno++;}
";"                { return T_END_CMD;}
","                { return T_SEPARATOR;}
[a-z][a-zA-Z0-9]*  {  yylval.string = yytext; return T_IDENTIFIER;}
[\t ]              {}
.                  { return T_ERROR; }

%%
    /* Procedures */
