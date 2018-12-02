#include "CommandStatement.h"


//
// Convert the command to code
//
void CommandStatement::toCode(FILE* output, bool isLibrary, int level) const {
	fprintf(output,"Command %c\n",this->command);
}
