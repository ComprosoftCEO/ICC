#ifndef LABEL_STATEMENT
#define LABEL_STATEMENT

#include "Statement.h"
#include <string>

class LabelStatement: public Statement {

private:
	std::string label;	//Label to jump to

public:

	LabelStatement(const std::string& label) :
	  Statement(StatementType::LABEL), label(label) {}

	LabelStatement(StatementType type, const std::string& label):
		Statement(type), label(label) {}

	const std::string& getLabel() const {
		return this->label;
	}

	void toCode(FILE* output, bool isLibrary, int level) const;
};

#endif
