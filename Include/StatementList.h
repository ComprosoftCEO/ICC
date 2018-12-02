#ifndef STATEMENT_LIST_HEADER
#define STATEMENT_LIST_HEADER

#include "Statement.h"
#include <vector>

//Stores a list of statements
class StatementList {

private:
	std::vector<Statement*> statements;

public:
	StatementList();
	~StatementList();

	void addStatement(Statement* statement);

	unsigned long size();

	void toCode(FILE* output, bool isLibrary, int level) const;
};

#endif
