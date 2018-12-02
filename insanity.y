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

insanity:
	%empty
	| '{' insanity '}'		{printf("IFs\n");}
	| ':' LABEL '}'			{printf("Read Label Definition: %s\n", $<label>1);}
	| '(' LABEL ')'			{printf("Read Jump Definition: %s\n", $<label>1);}
	| '[' LABEL ']'			{printf("Read Subroutine: %s\n", $<label>1);}
	| insanity COMMAND		{printf("Read Command: %c\n", $<cmd>2);}
	| COMMAND				{printf("Read Command: %c\n", $<cmd>1);}
	;

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
