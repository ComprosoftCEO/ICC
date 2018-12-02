#include <LibraryCallStatement.h>
#include <CodeSegment.h>


//
// Constructor
//
LibraryCallStatement::LibraryCallStatement(const std::string& label):
	  LabelStatement(StatementType::LIBRARY_CALL,label) {}



//
// Convert to code
//	
void LibraryCallStatement::toCode(FILE* output, bool isLibrary, int level) const {
	defineLibraryCall(output,this->getLabel(),isLibrary,level);
}
