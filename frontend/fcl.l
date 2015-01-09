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
"var"              { return T_VAR;}
"="               { return T_ASSIGN;}
"client"           { return T_CLIENT;}
"for"              { return T_FOR;}
"in"               { return T_IN;}
"("                { return T_LEFT;}
")"                { return T_RIGHT;}
"{"                { return T_BEGIN;}
"}"                { return T_END;}
\"[^\"]*\"         {
                      yylval.string.string = yytext + 1;
                      yylval.string.length = yyleng - 2;
                      return T_STRING;
                   }
[0-9]+             {
                      yylval.integer = atoi(yytext);
                      return T_INTEGER;
                   }
\n                 { yylineno++;}
";"                { return T_END_CMD;}
","                { return T_SEPARATOR;}
[a-z][a-zA-Z0-9]*  {
                        yylval.string.string = yytext;
                        yylval.string.length = yyleng;
                        return T_IDENTIFIER;
                    }
[\t ]              {}
.                  { return T_ERROR; }

%%
    /* Procedures */
