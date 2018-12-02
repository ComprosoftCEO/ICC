#include <InsanityParser.h>
#include <JumpStatement.h>


//
// Constructor
//
JumpStatement::JumpStatement(const std::string& label) :
	  LabelStatement(StatementType::JUMP, label) {}


//
// Convert to code
//
void JumpStatement::toCode(FILE* output, bool isLibrary, int level) const {
	printLevel(output,level);
	fprintf(output,"Jump %s\n",this->getLabel().c_str());
}

