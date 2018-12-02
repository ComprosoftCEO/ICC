#include <CodeSegment.h>
using std::set;
using std::string;
using std::map;


//
// Print number of tabs for the level
//
static void printLevel(FILE* file, int level) {
	for (int i = 0; i < level; ++i) {
		fprintf(file,"\t");
	}
}


//
// Header Code
//
void headerCode(FILE* file) {

	//1. Includes
	fprintf(file,"#include <stdio.h>\n");
	fprintf(file,"#include <stdlib.h>\n");
	fprintf(file,"#include <stdbool.h>\n");
	fprintf(file,"#include <stddef.h>\n\n");

	//2. Structure definitions
	fprintf(file,"typedef struct {\n");
	fprintf(file,"\tchar* key;\n");
	fprintf(file,"\tvoid* value;\n");
	fprintf(file,"} LibraryData_t;\n\n");

	fprintf(file,"typedef struct Insanity_t {\n");
	fprintf(file,"\tshort acc;\n");
	fprintf(file,"\tshort bak;\n");
	fprintf(file,"\tbool overflow;\n");
	fprintf(file,"\tbool compare;\n");
	fprintf(file,"\tshort mc;\n");
	fprintf(file,"\tchar dig;\n");
	fprintf(file,"\tshort memory[1000];\n");
	fprintf(file,"\tvoid* stack[100];\n");
	fprintf(file,"\tshort sp;\n");
	fprintf(file,"\tint argc;\n");
	fprintf(file,"\tchar** argv;\n");
	fprintf(file,"\tLibraryData_t* data;\n");
	fprintf(file,"\tsize_t dataLen;\n");
	fprintf(file,"\tsize_t dataAlloc;\n");
	fprintf(file,"} Insanity_t, *pInsanity_t;\n\n");

}



//
// Main Function Definition
//
void mainFunction(FILE* file) {
	fprintf(file,"int main(int argc, char** argv) {\n");
}
void endMain(FILE* file) {
	fprintf(file,"\treturn 0;\n");
	fprintf(file,"}\n");
}


//
// Shared library "Main" function
//
void mainSharedFunction(FILE* file,const map<string,int> libs) {
	fprintf(file,"static bool RunSharedLibrary(pInsanity_t insanity, int entryPoint) {\n");

	//Define the jump table
	fprintf(file,"\tstatic const void* const JUMP_TABLE[] = {\n");

	map<string,int>::const_iterator it;
	for (it = libs.begin(); it != libs.end(); ++it) {
		fprintf(file,"\t\t&&%s,\n",it->first.c_str());
	}
	fprintf(file,"\t};\n\n");

	fprintf(file,"\tgoto *(JUMP_TABLE[entryPoint]);\n");
}

void endSharedMain(FILE* file) {
	fprintf(file,"\treturn true;\n");
	fprintf(file,"\t}\n");
}


//
// Library Definitions (for calling another shared library)
//
void defineLibraryCalls(FILE* file,const set<string>& libs) {

	set<string>::const_iterator it;
	for (it = libs.begin(); it != libs.end(); ++it) {
		fprintf(file,"bool %s(pInsanity_t insanity);\n",(*it).c_str());
	}
	fprintf(file,"\n");
}


//
// Library Labels (for a shared library)
//
void defineLibraryLabels(FILE* file, const map<string,int> libs) {

	map<string,int>::const_iterator it;
	for (it = libs.begin(); it != libs.end(); ++it) {
		const string& str = it->first;
		int id = it->second;

		fprintf(file,"bool %s(pInsanity_t insanity) {\n",str.c_str());
		fprintf(file,"\treturn RunSharedLibrary(insanity,%d);\n",id);
		fprintf(file,"}\n\n");
	}
}




//
// Label Statements
//
void defineLabel(FILE* file, const string& label, int level) {
	printLevel(file,level);
	fprintf(file,"%s:\n",label.c_str());
}

void jump(FILE* file, const string& label, int level) {
	printLevel(file,level);
	fprintf(file,"goto %s;\n",label.c_str());
}

void subroutine(FILE* file, const string& label, bool isLibrary, int level) {

}

void libraryCall(FILE* file, const std::string& label, bool isLibrary, int level) {
	//printLevel(file,level);
}

void returnFrom(FILE* file, bool isLibrary) {

}


//
// If statements
//
void beginIf(FILE* file, int level) {
	printLevel(file,level);
	fprintf(file,"if (insanity->compare) {\n");
}

void endIf(FILE* file, int level) {
	printLevel(file,level);
	fprintf(file,"}\n");
}


//
// Memory Cursors
//
void cursorRight(FILE* file) {

}

void cursorLeft(FILE* file) {

}

void increase10(FILE* file) {

}

void decrease10(FILE* file) {

}

void resetCursors(FILE* file) {

}


//
// Memory and registers
//
void uploadACC(FILE* file) {

}

void swapMemory(FILE* file) {

}

void saveBackup(FILE* file) {

}

void swapBackup(FILE* file) {

}


//
// Maths
//
void add(FILE* file) {

}

void sub(FILE* file) {

}

void addBackup(FILE* file) {

}

void negate(FILE* file) {

}

void resetACC(FILE* file) {

}

void randomNumber(FILE* file) {

}


//
// Comparisons
//
void EQU(FILE* file) {

}

void NEQ(FILE* file) {

}

void GTR(FILE* file) {

}

void LSS(FILE* file) {

}

void testOverflow(FILE* file) {

}


//
// I/O functions
//
void getUserInput(FILE* file) {

}

void outputChar(FILE* file) {

}

void pause(FILE* file) {

}
