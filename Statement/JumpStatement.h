#ifndef JUMP_STATEMENT
#define JUMP_STATEMENT

#include "LabelStatement.h"

class JumpStatement: public LabelStatement {
	JumpStatement(const std::string& label) :
	  LabelStatement(StatementType::JUMP, label) {}

	void toCode() const;
};

#endif	/* Jump Statement Included */
