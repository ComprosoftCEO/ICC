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
	std::string* label;	// Label name
	char cmd;			// Single character command
}


%token <label> LABEL
%token <cmd> COMMAND

%%

//List of statements
insanity
	: /* Empty */
	| insanity statement	{printf("Read Statement!\n");}


//Single statement
statement
	: COMMAND				{printf("Read Command: %c\n", $<cmd>1);}
	| ':' label ':'			{printf("Read Label: %s\n", $<label>2->c_str());}
	| if
	| jump					{printf("Read Jump: %s\n", $<label>1->c_str());}
	| subroutine			{printf("Read Subroutine: %s\n", $<label>1->c_str());}


//A Label is a non-empty list of LABEL tokens
label
	: LABEL						{$<label>$ = $<label>1;}
	| label LABEL				{$<label>1->append(*$<label>2); delete($<label>2);}


//Special sub-statements
if:			'{' insanity '}' 	{printf("Read If\n");}
jump:       '(' label ')'		{$<label>$ = $<label>2;}
subroutine: '[' label ']'		{$<label>$ = $<label>2;}


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
