#include "SubroutineStatement.h"

//
// Constructor
//
SubroutineStatement::SubroutineStatement(const std::string& label):
	LabelStatement(StatementType::SUBROUTINE,label) {}

//
// To Code
//
void SubroutineStatement::toCode(FILE* output, bool isLibrary, int level) const {
	//Does nothing right now
}

