#ifndef STATEMENT_HEADER
#define STATEMENT_HEADER

#include <cstdio>	/* For FILE* */

//All types of Insanity statements
enum class StatementType {
	COMMAND,
	LABEL,
	JUMP,
	SUBROUTINE,
	LIBRARY_CALL,
	IF_STATEMENT
};


//Generic statement class
class Statement {

private:
	StatementType type;

public:
	Statement(StatementType type);
	virtual ~Statement() = default;


	StatementType getType() const;

	//Get the C code output for this statement
	//	output    = The file to write to
	//	isLibrary = If true, write as library code
	//	level	  = Number of tabs
	virtual void toCode(FILE* output, bool isLibrary, int level) const = 0;
};


#endif	/* Statement Header Included */
