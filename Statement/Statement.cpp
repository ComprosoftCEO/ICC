#include "Statement.h"

//
// Constructor
//
Statement::Statement(StatementType type) : type(type) {}


//
// Get the statement type
//
StatementType Statement::getType() const {
	return this->type;
}
