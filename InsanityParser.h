#ifndef INSANITY_PARSER_HEADER
#define INSANITY_PARSER_HEADER

#include <fstream>
#include <vector>
#include <map>

#include "Statement/Statement.h"
#include "Statement/CommandStatement.h"
#include "Statement/JumpStatement.h"
#include "Statement/SubroutineStatement.h"
#include "Statement/LibraryCallStatement.h"
#include "Statement/IfStatement.h"
#include "Statement/StatementList.h"


// Entire insanity program
class InsanityProgram {

private:
	std::vector<Statement*> program;
	std::map<std::string, size_t> labels;
	std::vector<Statement*> unresolvedLabels;
	bool isLibrary;


private:

	//Construct a new Insanity Program
	InsanityProgram(bool isLibrary);


	void insertIf();
	void exitIf();


public:
	~InsanityProgram();

	static InsanityProgram* readProgram(bool isLibrary, std::ifstream file);
	void printError();
};

#endif
