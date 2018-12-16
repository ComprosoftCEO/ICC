#include <InsanityParser.h>
#include "insanity.tab.h"
#include "insanity.yy.h"
#include <cstdio>
#include <iostream>
using std::string;


int main(int argc, char** argv) {

	if (argc < 2) {
		fprintf(stderr,"icc: Error! No input file given!\n");
		fprintf(stderr,"Usage: %s <infile> [outfile]\n",argv[0]);
		return 3;
	}


	//Open the file for reading
	FILE* file = fopen(argv[1],"r");
	if (file == NULL) {
		fprintf(stderr,"Error opening file '%s'!\n",argv[1]);
		return 1;
	}


	//Get everything ready to parse
	InsanityProgram* program = new InsanityProgram;
	yyscan_t scanner;          
	yylex_init(&scanner);
	yyset_in(file,scanner);

	int result = yyparse(scanner,program);

	yylex_destroy(scanner);
	fclose(file);

	if (result != 0) {
		return delete(program), 1;
	}

	//Output the program to the file
	string outfile = argv[1];
	if (argc > 2) {outfile = argv[2];} else {outfile += ".c";}
	if (!program->toProgram(outfile.c_str())) {
		return delete(program),2;
	}
	delete program;

	
	return 0;
}
