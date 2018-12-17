%define api.pure full
%locations

%parse-param { yyscan_t scanner } 
%lex-param {yyscan_t scanner}
%parse-param {InsanityProgram* program}

%code top {
	#include <cstdio>
	#include <cstdlib>
	#include <string>
	#include <InsanityParser.h>
}

%code requires {
	// Declare stuff from Flex that Bison needs to know about:
	typedef void* yyscan_t;
}

%code {
	int yylex(YYSTYPE* yylvalp, YYLTYPE* yyllocp, yyscan_t scanner);
	static void yyerror(YYLTYPE* yyllocp, yyscan_t unused, InsanityProgram* program, const char* msg);
}


%union {
	std::string* label;		// Label name
	char cmd;				// Single character command
	Statement* stmt;		// Single Insanity Statement
	StatementList* list;	// List of statements
}

%destructor {delete($$);} <label> <stmt> <list>


//Terminal types
%token <label> LABEL
%token <cmd> COMMAND

%token LIBSUBOPEN  "[{"
%token LIBSUBCLOSE "}]"
%token LIBLBLOPEN  ":{"
%token LIBLBLCLOSE "}:"

//Nonterminal types
%type <list> insanity if
%type <stmt> statement
%type <label> lblName label jump subroutine libraryLabel libraryCall

%%

//Top level function
code: insanity				{program->setList($<list>1);}


//List of statements
insanity
	:						{$<list>$ = new StatementList();}
	| insanity statement	{$<list>1->addStatement($<stmt>2); $<list>$ = $<list>1;}


//Single statement
statement
	: COMMAND				{$$ = new CommandStatement($1);}
	| if					{$$ = new IfStatement($1);}
	| label					{$$ = new LabelStatement(*$1);			program->labelDefinition(*$1);	delete($1);}
	| jump					{$$ = new JumpStatement(*$1);			program->labelCall(*$1);		delete($1);}
	| subroutine			{$$ = new SubroutineStatement(*$1);		program->labelCall(*$1); 		delete($1);}
	| libraryLabel			{$$ = new LabelStatement(*$1);			program->libraryLabel(*$1);		delete($1);}
	| libraryCall			{$$ = new LibraryCallStatement(*$1);	program->libraryCall(*$1);		delete($1);}


//A Label Name is a non-empty list of LABEL tokens
lblName
	: LABEL			{$$ = $1;}
	| lblName LABEL	{$1->append(*$2); $$ = $1; delete($2);}


//If statements
if:			'{' insanity '}'	 	{$$ = $2;}

//Label statements
label:		':' lblName ':'			{$$ = $2;}
jump:       '(' lblName ')'			{$$ = $2;}
subroutine: '[' lblName ']'			{$$ = $2;}

//Library functions
libraryLabel: ":{" lblName "}:"		{$$ = $2;}
libraryCall:  "[{" lblName "}]"		{$$ = $2;}

%%


static void yyerror(YYLTYPE* yyllocp, yyscan_t unused, InsanityProgram* program, const char *msg) {
	fprintf(stderr, "%s! [Line %d:%d]\n",
		msg,yyllocp->first_line, yyllocp->first_column);
}
