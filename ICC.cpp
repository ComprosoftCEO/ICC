#include <InsanityParser.h>
#include "insanity.tab.hpp"
#include <cstdio>
#include <iostream>

extern FILE *yyin;

int main(int argc, char** argv) {

	if (argc < 2) {
		fprintf(stderr,"icc: Error! No input file given!\n");
		fprintf(stderr,"Usage: %s <FileName>\n",argv[0]);
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
	yyin = file;

	int result = yyparse(program);
	fclose(file);

	if (result != 0) {
		return delete(program), 1;
	}

	//Output the program to the file
	if (!program->toProgram(stdout)) {
		return delete(program),2;
	}
	delete program;

	
	return 0;
}
