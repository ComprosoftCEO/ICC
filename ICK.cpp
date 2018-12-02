#include <InsanityParser.h>
#include "insanity.tab.hpp"
#include <cstdio>
#include <iostream>

extern FILE *yyin;

int main(int argc, char** argv) {

	if (argc < 2) {
		std::cout << "Usage: " << argv[0] << " <FileName>" << std::endl;
		return 0;
	}


	//Open the file for reading
	FILE* file = fopen(argv[1],"r");
	if (file == NULL) {
		std::cout << "Error Opening File!" << std::endl;
		return 1;
	}

	//Get everything ready to parse
	InsanityProgram* program = new InsanityProgram;
	yyin = file;
	
	yyparse(program);

	program->toProgram(stdout);
	delete program;

	return 0;
}
