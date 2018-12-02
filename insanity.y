%{
#include <cstdio>
#include <cstdlib>
#include <string>
#include <InsanityParser.h>

// Declare stuff from Flex that Bison needs to know about:
extern int yylex();
extern int yyparse();
extern FILE *yyin;
 
void yyerror(InsanityProgram* program, const char *s);
%}

%union {
	std::string* label;		// Label name
	char cmd;				// Single character command
	Statement* stmt;		// Single Insanity Statement
	StatementList* list;	// List of statements
}


%token <label> LABEL
%token <cmd> COMMAND

%token LIBSUBOPEN LIBSUBCLOSE
%token LIBLBLOPEN LIBLBLCLOSE
%parse-param {InsanityProgram* program}

%%

//Top level function
code: insanity				{program->setList($<list>1);}


//List of statements
insanity
	:						{$<list>$ = new StatementList();}
	| insanity statement	{$<list>1->addStatement($<stmt>2); $<list>$ = $<list>1;}


//Single statement
statement
	: COMMAND				{$<stmt>$ = new CommandStatement($<cmd>1);}
	| if					{$<stmt>$ = new IfStatement($<list>1);}
	| label					{$<stmt>$ = new LabelStatement(*$<label>1); 	  program->labelDefinition(*$<label>1); delete($<label>1);}
	| jump					{$<stmt>$ = new JumpStatement(*$<label>1); 		  program->labelCall(*$<label>1);		delete($<label>1);}
	| subroutine			{$<stmt>$ = new SubroutineStatement(*$<label>1);  program->labelCall(*$<label>1); 		delete($<label>1);}
	| libraryLabel			{$<stmt>$ = new LabelStatement(*$<label>1);		  program->libraryLabel(*$<label>1);	delete($<label>1);}
	| libraryCall			{$<stmt>$ = new LibraryCallStatement(*$<label>1); program->libraryCall(*$<label>1);		delete($<label>1);}


//A Label Name is a non-empty list of LABEL tokens
lblName
	: LABEL			{$<label>$ = $<label>1;}
	| lblName LABEL	{$<label>1->append(*$<label>2); delete($<label>2);}


//Special sub-statements
label:		':' lblName ':'				{$<label>$ = $<label>2;}
if:			'{' insanity '}'		 	{$<list>$ = $<list>2;}
jump:       '(' lblName ')'				{$<label>$ = $<label>2;}
subroutine: '[' lblName ']'				{$<label>$ = $<label>2;}

//Library functions
libraryLabel: LIBLBLOPEN lblName LIBLBLCLOSE	{$<label>$ = $<label>2;}
libraryCall:  LIBSUBOPEN lblName LIBSUBCLOSE	{$<label>$ = $<label>2;}

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
	InsanityProgram* program = new InsanityProgram;
	yyparse(program);

	program->toProgram(stdout);
	delete program;
	return 0;
}

void yyerror(InsanityProgram* program, const char *s) {
	printf("Parse Error! Message: %s\n",s);
	exit(-1);
}
