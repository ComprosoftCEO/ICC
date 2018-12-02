#include "JumpStatement.h"
#include "SubroutineStatement.h"
#include "LibraryCallStatement.h"



//
// Label to Code
//
void LabelStatement::toCode(FILE* output, bool isLibrary, int level) const {}

//
// Jump to Code
//
void JumpStatement::toCode(FILE* output, bool isLibrary, int level) const {}


//
// Subroutine to code
//
void SubroutineStatement::toCode(FILE* output, bool isLibrary, int level) const {}


//
// Library Call to Code
//
void LibraryCallStatement::toCode(FILE* output, bool isLibrary, int level) const {}
