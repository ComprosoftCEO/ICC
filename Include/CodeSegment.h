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
void returnFrom(FILE* file, bool isLibrary);


//If statements
void beginIf(FILE* file, int level);
void endIf(FILE* file, int level);


//Cursors
void cursorRight(FILE* file);
void cursorLeft(FILE* file);
void increase10(FILE* file);
void decrease10(FILE* file);
void resetCursors(FILE* file);


//Memory and Registers
void uploadACC(FILE* file);
void swapMemory(FILE* file);
void saveBackup(FILE* file);
void swapBackup(FILE* file);


//Maths
void add(FILE* file);
void sub(FILE* file);
void addBackup(FILE* file);
void negate(FILE* file);
void resetACC(FILE* file);
void randomNumber(FILE* file);


//Comparisons
void EQU(FILE* file);
void NEQ(FILE* file);
void GTR(FILE* file);
void LSS(FILE* file);
void testOverflow(FILE* file);


// Input and Output (I/O)
void getUserInput(FILE* file);
void outputChar(FILE* file);
void pause(FILE* file);

#endif
