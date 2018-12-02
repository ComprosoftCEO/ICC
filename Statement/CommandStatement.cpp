#include <InsanityParser.h>
#include <CommandStatement.h>


//
// Constructor
//
CommandStatement::CommandStatement(char command) :
	Statement(StatementType::COMMAND), command(command) {}


//
// Get the character command
//
char CommandStatement::getCommand() const {
	return this->command;
}


//
// Convert to printable code (lots of different types here)
//
void CommandStatement::toCode(FILE* output, bool isLibrary, int level) const {
	printLevel(output,level);
	fprintf(output,"Command: %c\n",this->command);
}
