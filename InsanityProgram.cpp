#include "InsanityProgram.cpp"
using std::vector;
using std::map;
using std::string;


//
// Constructor
//
InsanityProgram::InsanityProgram(bool isLibrary) : isLibrary(isLibrary) {}


//
// Destructor
//
InsanityProgram::~InsanityProgram() {

	//Delete all of the commands
	vector<Command*>::iterator it;
	for (it = program.begin(); it != program.end(); ++it) {
		delete *it;
	}
}

