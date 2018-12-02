#ifndef COMMAND_STATEMENT_HEADER
#define COMMAND_STATEMENT_HEADER

#include "Statement.h"

class CommandStatement: public Statement {

private:
	char command;

public:
	CommandStatement(char command) :
	  Statement(StatementType::COMMAND), command(command) {}
	~CommandStatement() = default;

	char getCommand() const {return this->command;}
	void toCode() const;
};


#endif	/* Command Statement Header Included */
