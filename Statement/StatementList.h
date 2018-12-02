#ifndef STATEMENT_LIST_HEADER
#define STATEMENT_LIST_HEADER

#include "Statement.h"
#include <vector>

//Stores a list of statements
class StatementList {

private:
	std::vector<Statement*> statements;

public:
	StatementList() {}
	~StatementList() {
		//Delete all statements
		std::vector<Statement*>::iterator it;
		for (it = statements.begin(); it != statements.end(); ++it) {
			delete *it;
		}
	}

	void addStatement(Statement* statement) {
		statements.push_back(statement);
	}


	void toCode(FILE* output, bool isLibrary, int level) const {}
};

#endif
