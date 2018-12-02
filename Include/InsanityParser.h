#ifndef INSANITY_PARSER_HEADER
#define INSANITY_PARSER_HEADER

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
	std::set<std::string> external;			// List of external library calls
	bool isLibrary;


public:
	InsanityProgram(bool isLibrary);
	~InsanityProgram();

	//Validate labels and calls as they are found in the program
	void resolveLabel(const std::string& label);
	void unresolvedLabel(const std::string& label);
	void addExternal(const std::string& call);


	void setList(StatementList* newList);
	StatementList* getList();

	void toProgram();
};

#endif
