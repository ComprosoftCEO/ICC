#ifndef INSANITY_PARSER_HEADER
#define INSANITY_PARSER_HEADER

#include <set>

//All of the statement types
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
	StatementList* list;
	std::set<std::string> unresolved;		// List of unresolved labels
	std::set<std::string> resolved;			// List of resolved labels
	std::set<std::string> external;			// List of external library calls
	bool isLibrary;


public:
	InsanityProgram(bool isLibrary): isLibrary(isLibrary) {}
	~InsanityProgram() {delete list;}

	//Validate labels and calls as they are found in the program
	void resolveLabel(const std::string& label) {
		this->resolved.insert(label);
		this->unresolved.erase(label);
	}

	void unresolvedLabel(const std::string& label) {
		if (this->resolved.find(label) != this->resolved.end()) {
			this->unresolved.insert(label);
		}
	}


	void addExternal(const std::string& call) {
		this->external.insert(call);
	}



	//Might cause a seg fault or memory leak if not careful
	void setList(StatementList* newList) {this->list = newList;}

	void toProgram();
};

#endif
