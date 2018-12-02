#ifndef INSANITY_PARSER_HEADER
#define INSANITY_PARSER_HEADER

#include <cstdio>
#include <set>

//All of the statement types
#include "Statement.h"
#include "CommandStatement.h"
#include "JumpStatement.h"
#include "SubroutineStatement.h"
#include "LibraryCallStatement.h"
#include "IfStatement.h"
#include "StatementList.h"


// Entire insanity program
class InsanityProgram {

private:
	StatementList* list;
	std::set<std::string> unresolved;		// List of unresolved labels
	std::set<std::string> resolved;			// List of resolved labels
	std::set<std::string> duplicate;		// Duplicate labels

	std::set<std::string> libLabel;			// List of library labels
	std::set<std::string> libCall;			// List of external library calls


public:
	InsanityProgram();
	~InsanityProgram();

	//Test if this will compile to a library or a program
	bool isLibrary() const;


	//Validate labels as they are found in the program
	//	Makes sure there are no duplicate labels, and that every call has a label to jump to
	void labelDefinition(const std::string& label);
	void labelCall(const std::string& label);

	//Also store any library calls or library entry points
	void libraryLabel(const std::string& label);
	void libraryCall(const std::string& call);


	//Update the internal list of statements
	void setList(StatementList* newList);
	StatementList* getList() const;


	//Returns false on error
	bool toProgram(FILE* file) const;
};



void printLevel(FILE* file, int level);

#endif
