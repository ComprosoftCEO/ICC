#ifndef IF_STATEMENT_HEADER
#define IF_STATEMENT_HEADER

#include "Statement.h"
#include "StatementList.h"

class IfStatement : public Statement {

private:
	StatementList* list;

public:
	IfStatement(StatementList* list) :
	  Statement(StatementType::IF_STATEMENT), list(list) {}
	
	void toCode() const {}

};

#endif
