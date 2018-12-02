#include <IfStatement.h>
#include <CodeSegment.h>


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
	beginIf(output,level);
	this->list->toCode(output,isLibrary,level+1);
	endIf(output,level);
}
