#include <InsanityParser.h>
#include <LibraryCallStatement.h>


//
// Constructor
//
LibraryCallStatement::LibraryCallStatement(const std::string& label):
	  LabelStatement(StatementType::LIBRARY_CALL,label) {}



//
// Convert to code
//	
void LibraryCallStatement::toCode(FILE* output, bool isLibrary, int level) const {
	printLevel(output,level);
	fprintf(output,"Library Call: %s\n",this->getLabel().c_str());
}
