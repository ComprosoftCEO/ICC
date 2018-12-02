#include <InsanityParser.h>
#include <SubroutineStatement.h>

//
// Constructor
//
SubroutineStatement::SubroutineStatement(const std::string& label):
	LabelStatement(StatementType::SUBROUTINE,label) {}

//
// To Code
//
void SubroutineStatement::toCode(FILE* output, bool isLibrary, int level) const {
	printLevel(output,level);
	fprintf(output,"Subroutine: %s\n",this->getLabel().c_str());
}

