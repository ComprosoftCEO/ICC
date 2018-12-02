#ifndef JUMP_STATEMENT
#define JUMP_STATEMENT

#include "LabelStatement.h"

class JumpStatement: public LabelStatement {

public:
	JumpStatement(const std::string& label);

	void toCode(FILE* output, bool isLibrary, int level) const;
};

#endif	/* Jump Statement Included */
