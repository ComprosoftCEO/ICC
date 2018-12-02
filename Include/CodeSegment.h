#ifndef CODE_SEGMENT_HEADER
#define CODE_SEGMENT_HEADER

#include <cstdio>

#include <set>
#include <map>
#include <vector>


//Functions to print out the code
void headerCode(FILE* file);

void mainFunction(FILE* file);
void endMain(FILE* file);
void mainSharedFunction(FILE* file,const std::map<std::string,int> libs);
void endSharedMain(FILE* file);

void defineLibraryCalls(FILE* file,const std::set<std::string>& libs);
void defineLibraryLabels(FILE* file, const std::map<std::string,int> libs);


//Label Commands
void defineLabel(FILE* file, const std::string& label, int level);
void jump(FILE* file, const std::string& label, int level);
void subroutine(FILE* file, const std::string& label, bool isLibrary, int level);
void libraryCall(FILE* file, const std::string& label, bool isLibrary, int level);
void returnFrom(FILE* file, bool isLibrary, int level);


//If statements
void beginIf(FILE* file, int level);
void endIf(FILE* file, int level);


//Cursors
void cursorRight(FILE* file, bool isLibrary, int level);
void cursorLeft(FILE* file, bool isLibrary, int level);
void increase10(FILE* file, bool isLibrary, int level);
void decrease10(FILE* file, bool isLibrary, int level);
void resetCursors(FILE* file, bool isLibrary, int level);


//Memory and Registers
void uploadACC(FILE* file, bool isLibrary, int level);
void swapMemory(FILE* file, bool isLibrary, int level);
void saveBackup(FILE* file, bool isLibrary, int level);
void swapBackup(FILE* file, bool isLibrary, int level);


//Maths
void add(FILE* file, bool isLibrary, int level);
void sub(FILE* file, bool isLibrary, int level);
void addBackup(FILE* file, bool isLibrary, int level);
void negate(FILE* file, bool isLibrary, int level);
void resetACC(FILE* file, bool isLibrary, int level);
void randomNumber(FILE* file, bool isLibrary, int level);


//Comparisons
void EQU(FILE* file, bool isLibrary, int level);
void NEQ(FILE* file, bool isLibrary, int level);
void GTR(FILE* file, bool isLibrary, int level);
void LSS(FILE* file, bool isLibrary, int level);
void testOverflow(FILE* file, bool isLibrary, int level);


// Input and Output (I/O)
void getUserInput(FILE* file, bool isLibrary, int level);
void outputChar(FILE* file, bool isLibrary, int level);
void pause(FILE* file, bool isLibrary, int level);

#endif
