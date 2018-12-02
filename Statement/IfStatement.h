#ifndef IF_STATEMENT_HEADER
#define IF_STATEMENT_HEADER

#include "Statement.h"
#include "StatementList.h"

class IfStatement : public Statement {

private:
	StatementList* list;

public:
	IfStatement(StatementList* list);
	~IfStatement();
	
	void toCode(FILE* output, bool isLibrary, int level) const;
};

#endif
