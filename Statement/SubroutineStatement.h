#ifndef SUBROUTINE_STATEMENT
#define SUBROUTINE_STATEMENT

#include "LabelStatement.h"

class SubroutineStatement: public LabelStatement {

public:
	SubroutineStatement(const std::string& label):
	  LabelStatement(StatementType::SUBROUTINE, label) {}

	void toCode() const;
};

#endif	/* Subroutine Statement Included */
