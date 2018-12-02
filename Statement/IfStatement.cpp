#include <InsanityParser.h>
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
	printLevel(output,level);
	fprintf(output,"IF () {\n");

	this->list->toCode(output,isLibrary,level+1);

	printLevel(output,level);
	fprintf(output,"}\n");
}
