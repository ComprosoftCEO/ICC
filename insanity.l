%{
	#include "InsanityParser.h"
	#include "insanity.tab.h"

	//Track line numbers for parsed tokens
	#define YY_USER_ACTION                                             \
	yylloc->first_line = yylloc->last_line;                            \
	yylloc->first_column = yylloc->last_column;                        \
	if (yylloc->last_line == yylineno)                                 \
		yylloc->last_column += yyleng;                                 \
	else {                                                             \
		yylloc->last_line = yylineno;                                  \
		yylloc->last_column = yytext + yyleng - strrchr(yytext, '\n'); \
	}
%}

%x LBL
%x JUMP
%x SUB
%x LIBLBL
%x CALL

%option yylineno noyywrap 8bit nodefault                        
%option reentrant bison-bridge bison-locations 
%%


[\{\}]				{return yytext[0];}

[:]					{BEGIN(LBL);		return yytext[0];}
[(]					{BEGIN(JUMP);		return yytext[0];}
[[]					{BEGIN(SUB);		return yytext[0];}
[:][\{]				{BEGIN(LIBLBL);		return LIBLBLOPEN;}
[[][\{]				{BEGIN(CALL);		return LIBSUBOPEN;}
<LBL>[:]			{BEGIN(INITIAL); 	return yytext[0];}
<JUMP>[)]			{BEGIN(INITIAL);	return yytext[0];}
<SUB>[]]			{BEGIN(INITIAL);	return yytext[0];}
<LIBLBL>[\}][:]		{BEGIN(INITIAL);	return LIBLBLCLOSE;}
<CALL>[\}][]]		{BEGIN(INITIAL);	return LIBSUBCLOSE;}

<LBL,JUMP,SUB,LIBLBL,CALL>[a-zA-Z][a-zA-Z0-9]*		{yylval->label = new std::string(yytext); return LABEL;}
<LBL,JUMP,SUB,LIBLBL,CALL>.							/* Ignore unrecognized symbols */	
<LBL,JUMP,SUB,LIBLBL,CALL>\n						/* Ignore unrecognized symbols */	

[.;<>'"_^|$~+\-&`@%=*/\\!?#,]	{yylval->cmd = yytext[0]; return COMMAND;}
.								/* Ignore empty text */
\n								/* Ignore new lines */
