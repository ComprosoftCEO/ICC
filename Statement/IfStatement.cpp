#include <IfStatement.h>

//
// Constructor
//
IfStatement::IfStatement(StatementList* list) :
	  Statement(StatementType::IF_STATEMENT), list(list) {}


//
// Destructor
//
IfStatement::~IfStatement() {
	delete list;
}


//
// Convert to C code
//
void IfStatement::toCode(FILE* output, bool isLibrary, int level) const {
	//Does nothing right now
}
