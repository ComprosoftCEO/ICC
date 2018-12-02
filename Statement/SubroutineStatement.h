#ifndef SUBROUTINE_STATEMENT
#define SUBROUTINE_STATEMENT

#include "LabelStatement.h"

class SubroutineStatement: public LabelStatement {

public:
	SubroutineStatement(const std::string& label):
	  LabelStatement(StatementType::SUBROUTINE, label) {}

	~SubroutineStatement() = default;

	void toCode() const;
};

#endif	/* Subroutine Statement Included */
