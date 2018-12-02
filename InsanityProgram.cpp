#include <InsanityParser.h>


//
// Constructor
//
InsanityProgram::InsanityProgram(bool isLibrary): isLibrary(isLibrary) {}


//
// Destructor
//
InsanityProgram::~InsanityProgram() {delete list;}



//
//Validate labels and calls as they are found in the program
//	Also test for duplicate labels
void InsanityProgram::resolveLabel(const std::string& label) {
	this->resolved.insert(label);
	this->unresolved.erase(label);
}


//
// Add any jump or subroutine labels to the lists as well
//
void InsanityProgram::unresolvedLabel(const std::string& label) {
	if (this->resolved.find(label) != this->resolved.end()) {
		this->unresolved.insert(label);
	}
}


//
// Declare any external functions
//
void InsanityProgram::addExternal(const std::string& call) {
	this->external.insert(call);
}


//
// Update the list in the program
//	Might cause a segfault or memory leak if not careful
//
void InsanityProgram::setList(StatementList* newList) {
	this->list = newList;
}

StatementList* InsanityProgram::getList() {
	return this->list;
}


//
// Convert to a text program
//
void InsanityProgram::toProgram() {

}
