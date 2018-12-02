%{
#include <stdio.h>
#include <stdlib.h>

// Declare stuff from Flex that Bison needs to know about:
extern int yylex();
extern int yyparse();
extern FILE *yyin;
 
void yyerror(const char *s);
%}

%union {
	char *label;		// Label name
	char cmd;			// Single character command
}


%token <label> LABEL
%token <cmd> COMMAND

%%

//List of statements
insanity
	: /* Empty */
	| statement insanity	{printf("Read Statement!\n");}


//Single statement
statement
	: COMMAND				{printf("Read Command: %c\b", $<cmd>1);}
	| if
	| jump
	| subroutine
	| label

if:			'{' insanity '}' 	{printf("Read If\n");}
label: 		':' LABEL ':'		{printf("Read Label Definition: %s\n", $<label>2);}
jump:       '(' LABEL ')'		{printf("Read Jump Definition: %s\n", $<label>2);}
subroutine: '[' LABEL ']'		{printf("Read Subroutine: %s\n", $<label>2);}


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
