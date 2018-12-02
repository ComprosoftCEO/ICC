%{
	#include "insanity.tab.h"
%}

%x LBL

%option noyywrap
%option yylineno
%option stack
%%

\{					{printf("{\n"); return yytext[0];}
\}					{printf("}\n"); return yytext[0];}

[:([]				{printf("Begin %c\n",yytext[0]); BEGIN(LBL);   return yytext[0];}
<LBL>[]:)]			{printf("End %c\n",yytext[0]);	BEGIN(INITIAL); return yytext[0];}
<LBL>[a-zA-Z0-9]+	{
	printf("Label: %s\n",yytext);
	yylval.label = strdup(yytext);
	return LABEL;
}

[+*/]			{printf("Command: %c\n", yytext[0]); yylval.cmd = yytext[0]; return COMMAND;}
.				/* Ignore empty text */
