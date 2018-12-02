#ifndef LIBRARY_CALL_HEADER
#define LIBRARY_CALL_HEADER

#include "LabelStatement.h"

class LibraryCallStatement : public LabelStatement {

public:
	LibraryCallStatement(const std::string& label):
	  LabelStatement(StatementType::LIBRARY_CALL,label) {}
	
	void toCode(FILE* output, bool isLibrary, int level) const;
};


#endif	/* Library Call Header Included */
