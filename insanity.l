%{
	#include "insanity.tab.h"
%}


%option noyywrap
%option yylineno
%%

\{|\}|:|\[|\]	{yylval.cmd = yytext[0]; return yytext[0];}
[a-zA-z0-9]+	{yylval.label = yytext; return LABEL;}
[+*/]			{yylval.cmd = yytext[0]; return COMMAND;}
