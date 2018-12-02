%{
	#include "insanity.tab.hpp"
%}

%x LBL
%x JUMP
%x SUB
%x CALL

%option noyywrap
%option yylineno
%%


[\{\}]				{return yytext[0];}

[:]					{BEGIN(LBL);		return yytext[0];}
[(]					{BEGIN(JUMP);		return yytext[0];}
[[]\\\{				{BEGIN(CALL);		return yytext[0];}
[[]					{BEGIN(SUB);		return yytext[0];}
<LBL>[:]			{BEGIN(INITIAL); 	return yytext[0];}
<JUMP>[(]			{BEGIN(INITIAL);	return yytext[0];}
<SUB>[]]			{BEGIN(INITIAL);	return yytext[0];}
<CALL>[[]\\\}		{BEGIN(INITIAL);	return yytext[0];}

<LBL,JUMP,SUB,CALL>[a-zA-Z0-9]+		{yylval.label = strdup(yytext); return LABEL;}
<LBL,JUMP,SUB,CALL>.				/* Ignore unrecognized symbols */	

[;<>'"_^|$~+\-&`@%=*/\\!?#,]	{yylval.cmd = yytext[0]; return COMMAND;}
.								/* Ignore empty text */
