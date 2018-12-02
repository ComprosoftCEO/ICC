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
void defineGoto(FILE* file, const std::string& label, int level);
void defineSubroutine(FILE* file, const std::string& label, bool isLibrary, int level);
void defineLibraryCall(FILE* file, const std::string& label, bool isLibrary, int level);

//If statements
void beginIf(FILE* file, int level);
void endIf(FILE* file, int level);


#endif
