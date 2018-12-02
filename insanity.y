%{
#include <cstdio>
#include <cstdlib>
#include <string>
#include "InsanityParser.h"

// Declare stuff from Flex that Bison needs to know about:
extern int yylex();
extern int yyparse();
extern FILE *yyin;
 
void yyerror(const char *s);
%}

%union {
	std::string* label;		// Label name
	char cmd;				// Single character command
	Statement* stmt;		// Single Insanity Statement
	StatementList* list;	// List of statements
}


%token <label> LABEL
%token <cmd> COMMAND

%token LIBOPEN LIBCLOSE

%%

//List of statements
insanity
	:						{$<list>$ = new StatementList();}
	| insanity statement	{$<list>$->add($<stmt>2);}


//Single statement
statement
	: COMMAND				{$<stmt>$ = new CommandStatement($<cmd>1);}
	| ':' label ':'			{printf("Read Label: %s\n", $<label>2->c_str());}
	| if					{$<stmt>$ = new IfStatement($<list>1);}
	| jump					{$<stmt>$ = new JumpStatement(*$<label>1);}
	| subroutine			{$<stmt>$ = new SubroutineStatement(*$<label>1);}
	| library				{$<stmt>$ = new LibraryCallStatement(*$<label>1);}


//A Label is a non-empty list of LABEL tokens
label
	: LABEL			{$<label>$ = $<label>1;}
	| label LABEL	{$<label>1->append(*$<label>2); delete($<label>2);}


//Special sub-statements
if:			'{' insanity '}' 	{$<list>1 = $<list>2;}
jump:       '(' label ')'		{$<label>$ = $<label>2;}
subroutine: '[' label ']'		{$<label>$ = $<label>2;}
library: LIBOPEN label LIBCLOSE	{$<label>$ = $<label>2;}


%%

int main(int argc, char** argv) {

	// Open a file handle to a particular file:
	//FILE *myfile = fopen("insanity.file", "r");
	// Make sure it is valid:
	/*if (!myfile) {
		printf("I can't open insanity.file\n");
		return -1;
	}*/
	
	// Set Flex to read from it instead of defaulting to STDIN:
//	yyin = myfile;
	
	// Parse through the input:
	yyparse();
	
}

void yyerror(const char *s) {
	printf("Parse Error! Message: %s\n",s);
	exit(-1);
}
