#include <InsanityParser.h>
using std::string;
using std::set;


//
// Constructor
//
InsanityProgram::InsanityProgram(): labelID(0) {}


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
	return (this->libLabel.size() > 0);
}



//
// Add a label to the list of defined labels, testing for duplicates
//
void InsanityProgram::labelDefinition(const string& label) {
	if (this->resolved.count(label) > 0) {
		this->duplicate.insert(label);
	}

	this->resolved.insert(label);
	this->unresolved.erase(label);
}


//
// Add any jump or subroutine labels to the lists as well
//
void InsanityProgram::labelCall(const string& label) {
	if (this->resolved.count(label) <= 0) {
		this->unresolved.insert(label);
	}
}


//
// Define library entry points (testing for duplicates)
//
void InsanityProgram::libraryLabel(const string& label) {
	labelDefinition(label);

	//Each library call only gets one ID
	if (this->libLabel.count(label) <= 0) {
		this->libLabel[label] = labelID++;
	}
}

//
// Declare any external library calls
//
void InsanityProgram::libraryCall(const string& call) {
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
// Print out a set to the console
//
static void printSet(const char* message, const set<string> toPrint) {
	for (set<string>::const_iterator it = toPrint.begin(); it != toPrint.end(); ++it) {
		fprintf(stderr,"%s '%s'\n",message,(*it).c_str());
	}
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

	//Test for duplicate and unresolved labels
	bool fail = false;

	if (this->duplicate.size() > 0) {
		printSet("Duplicate Label",this->duplicate);
		fail = true;
	}
	if (this->unresolved.size() > 0) {
		printSet("Unresolved Label",this->unresolved);
		fail = true;
	}
	if (fail) {
		return false;
	}


	//Okay, write the code!!!
	headerCode(file);
	defineLibraryCalls(file,this->libCall);
	if (this->isLibrary()) {
		defineLibraryLabels(file,this->libLabel);

		mainSharedFunction(file,this->libLabel);
		  this->list->toCode(file,this->isLibrary(),1);
		endSharedMain(file);
	} else {
		mainFunction(file);
		  this->list->toCode(file,this->isLibrary(),1);
		endMain(file);
	}

	return true;
}


//
// Print number of tabs for the level
//
void printLevel(FILE* file, int level) {
	for (int i = 0; i < level; ++i) {
		fprintf(file,"\t");
	}
}
