#include <SubroutineStatement.h>
#include <CodeSegment.h>


//
// Constructor
//
SubroutineStatement::SubroutineStatement(const std::string& label):
	LabelStatement(StatementType::SUBROUTINE,label) {}

//
// To Code
//
void SubroutineStatement::toCode(FILE* output, bool isLibrary, int level) const {
	subroutine(output,this->getLabel(),isLibrary,level);
}

