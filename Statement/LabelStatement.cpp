#include "LabelStatement.h"

//
// Constructors
//
LabelStatement::LabelStatement(const std::string& label) :
  Statement(StatementType::LABEL), label(label) {}

LabelStatement::LabelStatement(StatementType type, const std::string& label):
	Statement(type), label(label) {}


//
// Get the label object
//
const std::string& LabelStatement::getLabel() const {
	return this->label;
}



//
// Convert this statement to code
//
void LabelStatement::toCode(FILE* output, bool isLibrary, int level) const {

}
