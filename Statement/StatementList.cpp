#include <StatementList.h>

//
// Constructor
//
StatementList::StatementList() {}


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
	this->statements.push_back(statement);
}



//
// Number of elements in the list
//
unsigned long StatementList::size() {
	return this->statements.size();
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
