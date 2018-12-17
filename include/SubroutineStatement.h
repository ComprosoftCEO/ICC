#ifndef SUBROUTINE_STATEMENT
#define SUBROUTINE_STATEMENT

#include "LabelStatement.h"

class SubroutineStatement: public LabelStatement {

public:
	SubroutineStatement(const std::string& label);

	void toCode(FILE* output, bool isLibrary, int level) const;
};

#endif	/* Subroutine Statement Included */
