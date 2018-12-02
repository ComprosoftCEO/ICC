#include "JumpStatement.h"


//
// Constructor
//
JumpStatement::JumpStatement(const std::string& label) :
	  LabelStatement(StatementType::JUMP, label) {}


//
// Convert to code
//
void JumpStatement::toCode(FILE* output, bool isLibrary, int level) const {
	//Does nothing right now
}

