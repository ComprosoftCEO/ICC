#ifndef STATEMENT_HEADER
#define STATEMENT_HEADER

//All types of Insanity statements
enum class StatementType {
	COMMAND,
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
	Statement(StatementType type): type(type) {}
	virtual ~Statement() = default;


	inline StatementType getType() const {
		return this->type;
	}

	//Get the C code output for this statement
	virtual void toCode() const = 0;
};


#endif	/* Statement Header Included */
