#ifndef LABEL_STATEMENT
#define LABEL_STATEMENT

#include "Statement.h"

class LabelStatement: public Statement {

private:
	std::string label;	//Label to jump to

public:
	LabelStatement(StatementType type, const std::string& label):
		Statement(type), label(label) {}

	const std::string& getLabel() const {
		return this->label;
	}
};

#endif
