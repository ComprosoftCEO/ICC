#include <InsanityParser.h>


//
// Constructor
//
InsanityProgram::InsanityProgram() {}


//
// Destructor
//
InsanityProgram::~InsanityProgram() {
	delete list;
}



//
// Test if this compiles to a library or a program
//	A library has at least one public library label
//
bool InsanityProgram::isLibrary() const {
	return this->libLabel.size() > 0;
}



//
// Add a label to the list of defined labels, testing for duplicates
//
void InsanityProgram::labelDefinition(const std::string& label) {
	if (this->resolved.find(label) != this->resolved.end()) {
		this->duplicate.insert(label);
	}

	this->resolved.insert(label);
	this->unresolved.erase(label);
}


//
// Add any jump or subroutine labels to the lists as well
//
void InsanityProgram::labelCall(const std::string& label) {
	if (this->resolved.find(label) != this->resolved.end()) {
		this->unresolved.insert(label);
	}
}


//
// Define library entry points (testing for duplicates)
//
void InsanityProgram::libraryLabel(const std::string& label) {
	labelDefinition(label);
	this->libLabel.insert(label);
}

//
// Declare any external library calls
//
void InsanityProgram::libraryCall(const std::string& call) {
	this->libCall.insert(call);
}


//
// Update the list in the program
//	Might cause a segfault or memory leak if not careful
//
void InsanityProgram::setList(StatementList* newList) {
	this->list = newList;
}

StatementList* InsanityProgram::getList() const {
	return this->list;
}


//
// Convert to a text program
//
bool InsanityProgram::toProgram(FILE* file) const {
	//Make sure we have statements
	if ((!list) || (list->size() <= 0)) {
		fprintf(stderr,"No program to compile!\n");
		return false;
	}


	this->list->toCode(file,this->isLibrary(),0);

}


//
// Print number of tabs for the level
//
void printLevel(FILE* file, int level) {
	for (int i = 0; i < level; ++i) {
		fprintf(file,"\t");
	}
}
