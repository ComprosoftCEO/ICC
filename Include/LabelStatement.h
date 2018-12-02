#ifndef LABEL_STATEMENT
#define LABEL_STATEMENT

#include "Statement.h"
#include <string>

class LabelStatement: public Statement {

private:
	std::string label;	//Label to jump to

public:

	LabelStatement(const std::string& label);
	LabelStatement(StatementType type, const std::string& label);

	const std::string& getLabel() const;

	virtual void toCode(FILE* output, bool isLibrary, int level) const;
};

#endif
