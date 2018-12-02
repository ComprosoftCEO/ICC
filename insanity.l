%{
	#include "insanity.tab.h"
%}

%x LBL

%option noyywrap
%option yylineno
%%


[\{\}]				{return yytext[0];}

[:([]				{BEGIN(LBL);   return yytext[0];}
<LBL>[]:)]			{BEGIN(INITIAL); return yytext[0];}
<LBL>[a-zA-Z0-9]+	{yylval.label = strdup(yytext); return LABEL;}
<LBL>.				{return yytext[0];}

[;<>'"_^|$~+\-&`@%=*/\\!?#,]	{yylval.cmd = yytext[0]; return COMMAND;}
.					/* Ignore empty text */
