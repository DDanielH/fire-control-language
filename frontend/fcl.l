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
\"[^\"]*\"        { return T_STRING;}
[0-9]+             { return T_INTEGER;}
\n                 { return T_NEWLINE;}
";"                { return T_END_CMD;}
","                { return T_SEPARATOR;}
[a-z][a-zA-Z0-9]*  { return T_IDENTIFIER;}

.                   { std::cerr << "ERROR" << std::endl; return T_ERROR; }

%%
    /* Procedures */
