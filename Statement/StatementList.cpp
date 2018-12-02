#include <StatementList.h>

//
// Constructor
//
StatementList::StatementList(): statements{nullptr} {}


//
// Destructor
//
StatementList::~StatementList() {
	//Delete all statements
	std::vector<Statement*>::iterator it;
	for (it = statements.begin(); it != statements.end(); ++it) {
		delete *it;
	}
}


//
// Add a statement to the list
//
void StatementList::addStatement(Statement* statement) {
	statements.push_back(statement);
}


//
// Convert to printable C code
//
void StatementList::toCode(FILE* output, bool isLibrary, int level) const {
	//Print all statements
	std::vector<Statement*>::const_iterator it;
	for (it = statements.begin(); it != statements.end(); ++it) {
		(*it)->toCode(output,isLibrary,level);
	}
}
