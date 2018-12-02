#include <CommandStatement.h>
#include <CodeSegment.h>
#include <map>
using std::map;

typedef void (*PrintFunc_t)(FILE*,bool,int);

static const map<char,PrintFunc_t> ALL_COMMANDS = {

	//Cursors
	{'<',	cursorLeft},
	{'>',	cursorRight},
	{'"',	increase10},
	{'\'',	decrease10},
	{'_',	resetCursors},

	//Memory and Registers
	{'^',	uploadACC},
	{'|',	swapMemory},
	{'$',	saveBackup},
	{'~',	swapBackup},

	//Maths
	{'+',	add},
	{'-',	sub},
	{'&',	addBackup},
	{'`',	negate},
	{'@',	resetACC},
	{'%',	randomNumber},

	//Comparisons
	{'=',	EQU},
	{'*',	NEQ},
	{'/',	GTR},
	{'\\',	LSS},
	{'!',	testOverflow},

	//Input and Output
	{'?',	getUserInput},
	{'#',	outputChar},
	{',',	pause}
};



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
	if (ALL_COMMANDS.count(this->command) > 0) {
		ALL_COMMANDS.at(this->command)(output,isLibrary,level);
	}
}
