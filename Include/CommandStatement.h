#ifndef COMMAND_STATEMENT_HEADER
#define COMMAND_STATEMENT_HEADER

#include "Statement.h"

class CommandStatement: public Statement {

private:
	char command;

public:
	CommandStatement(char command);

	char getCommand() const;
	void toCode(FILE* output, bool isLibrary, int level) const;
};


#endif	/* Command Statement Header Included */
