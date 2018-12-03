#include <CodeSegment.h>
#include <cstdarg>
using std::set;
using std::string;
using std::map;


//
// Print number of tabs for the level
//
static void printLevel(FILE* file, int level,const char* str,...) {
	for (int i = 0; i < level; ++i) {
		fprintf(file,"\t");
	}
	
	va_list vl;
	va_start(vl,str);
	  vfprintf(file,str,vl);
	va_end(vl);
}


//
// Mangle the name of a function or label
//
static std::string mangleLabel(const std::string& label) {
	return "Lbl_"+label;
}

static std::string mangleLibraryCall(const std::string& label) {
	return "Ins_"+label;
}



//
// Header Code
//
void headerCode(FILE* file) {

	//1. Includes
	fprintf(file,"#include <stdio.h>\n");
	fprintf(file,"#include <stdlib.h>\n");
	fprintf(file,"#include <stdbool.h>\n");
	fprintf(file,"#include <stddef.h>\n");
	fprintf(file,"#include <time.h>\n\n");

	//2. Some macros
	fprintf(file,"#define CLAMP(val,left,right) if ((val) < (left)) {(val) = (left);} else if ((val) > (right)) {(val) = (right);}\n");
	fprintf(file,"#define DIGIT(x) ((x) == 1 ? 10 : ((x) == 2) ? 100 : 1)\n");
	fprintf(file,"#define TEST_OVERFLOW(insanity,x) if (((x) < -999) || ((x) > 999)) {insanity->overflow = true;} else {insanity->overflow = false;}\n\n");

	//3. Structure definitions
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

	//4. Static Functions
	fprintf(file,"static void printChar(short int input) {\n");
	fprintf(file,"\tif (input >= 0 && input < 94) {printf(\"%%c\", input+32);}\n");
	fprintf(file,"\telse if (input >= 94) {printf(\"☺\");}\n");
	fprintf(file,"\telse if (input == -1) {printf(\"\\n\");}\n");
	fprintf(file,"\telse if (input == -999) {system(\"clear\");}\n");
	fprintf(file,"\telse {printf(\"☹️\");}\n");
	fprintf(file,"}\n\n");

	fprintf(file,"static short getUserInput(void) {\n");
	fprintf(file,"\tchar c;\n");
	fprintf(file,"\tdo {\n");
	fprintf(file,"\t\tc = fgetc(stdin);\n");
	fprintf(file,"\t} while ((c < 32) || (c > 126));\n");
	fprintf(file,"\treturn c-32;\n");
	fprintf(file,"}\n\n");

	fprintf(file,"static void pause(pInsanity_t insanity) {\n");
	fprintf(file,"\tprintf(\"Pause Program:\\n\");\n");
	fprintf(file,"\tprintf(\"--------------\\n\");\n");
	fprintf(file,"\tprintf(\"Acc:      %%-6d\\tBak:     %%-6d\\n\",insanity->acc,insanity->bak);\n");
	fprintf(file,"\tprintf(\"SP:       %%-6d\\n\",               insanity->sp);\n");
	fprintf(file,"\tprintf(\"Memory:   %%-6d\\tDigit:   %%-6d\\n\",insanity->mc,DIGIT(insanity->dig));\n");
	fprintf(file,"\tprintf(\"Overflow: %%-6d\\tCompare: %%-6d\\n\",insanity->overflow,insanity->compare);\n");
	fprintf(file,"\tprintf(\"\\nPress <Enter> to continue...\\n\");\n");
	fprintf(file,"\tfflush(stdout);\n");
	fprintf(file,"\twhile(fgetc(stdin) != '\\n');\n");
	fprintf(file,"}\n\n");
}



//
// Main Function Definition
//
void mainFunction(FILE* file) {
	fprintf(file,"int main(int argc, char** argv) {\n");

	//Initialization routine
	fprintf(file,"\tInsanity_t ins = {.sp = 99, .argc = argc, .argv = argv};\n");
	fprintf(file,"\tpInsanity_t insanity = &ins;\n");
	fprintf(file,"\tsrand(time(NULL));\n");
}
void endMain(FILE* file) {
	fprintf(file,"\t/*END*/ return 0;\n");
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
		fprintf(file,"\t\t[%d] = &&%s,\n",it->second,mangleLabel(it->first).c_str());
	}
	fprintf(file,"\t};\n\n");

	fprintf(file,"\tgoto *(JUMP_TABLE[entryPoint]);\n\n");
}

void endSharedMain(FILE* file) {
	fprintf(file,"\t/*RET*/ return true;\n");
	fprintf(file,"}\n");
}


//
// Library Definitions (for calling another shared library)
//
void defineLibraryCalls(FILE* file,const set<string>& libs) {

	set<string>::const_iterator it;
	for (it = libs.begin(); it != libs.end(); ++it) {
		fprintf(file,"bool %s(pInsanity_t insanity);\n",mangleLibraryCall(*it).c_str());
	}
	fprintf(file,"\n");
}


//
// Library Labels (for a shared library)
//
void defineLibraryLabels(FILE* file, const map<string,int> libs) {

	//Forward declare the run function
	fprintf(file,"static bool RunSharedLibrary(pInsanity_t insanity, int entryPoint);\n\n");

	map<string,int>::const_iterator it;
	for (it = libs.begin(); it != libs.end(); ++it) {
		const string& str = it->first;
		int id = it->second;

		fprintf(file,"bool %s(pInsanity_t insanity) {\n",mangleLibraryCall(str).c_str());
		fprintf(file,"\treturn RunSharedLibrary(insanity,%d);\n",id);
		fprintf(file,"}\n\n");
	}
}




//
// Label Statements
//
void defineLabel(FILE* file, const string& label, int level) {
	printLevel(file,level,"/*: :*/ %s: ;\n",mangleLabel(label).c_str());
}

void jump(FILE* file, const string& label, int level) {
	printLevel(file,level,"/*( )*/ goto %s;\n",mangleLabel(label).c_str());
}

void subroutine(FILE* file, const string& label, bool isLibrary, int level) {
	static int id = 0;	//Generate a unique ID for every Jump to Subroutine command

	printLevel(file,level,"/*[ ]*/ if (insanity->sp < 0) {\n");
	printLevel(file,level,"/*   */ \tprintf(\"Stack Overflow!\\n\");\n");
	printLevel(file,level,"/*   */ \treturn %s;\n",(isLibrary) ? "false" : "1");
	printLevel(file,level,"/*   */ } else {\n");
	printLevel(file,level,"/*   */ \tinsanity->stack[insanity->sp--] = &&SR_%d;\n",id);
	printLevel(file,level,"/*   */ \tgoto %s;\n",mangleLabel(label).c_str());
	printLevel(file,level,"/*   */ }\n");
	printLevel(file,level,"/*   */ SR_%d: ;\n",id++);
}

void libraryCall(FILE* file, const std::string& label, bool isLibrary, int level) {
	printLevel(file,level,"/*[{}*/ if (insanity->sp < 0) {\n");
	printLevel(file,level,"/*   */ \tprintf(\"Stack Overflow!\\n\");\n");
	printLevel(file,level,"/*   */ \treturn %s;\n",(isLibrary) ? "false" : "1");
	printLevel(file,level,"/*   */ } else {\n");
	printLevel(file,level,"/*   */ \tinsanity->stack[insanity->sp--] = 0;\n");
	printLevel(file,level,"/*   */ \tif (!%s(insanity)) {return %s;}\n",mangleLibraryCall(label).c_str(),(isLibrary) ? "false" : "1"); 
	printLevel(file,level,"/*   */ }\n");
}

void returnFrom(FILE* file, bool isLibrary, int level) {
	printLevel(file,level,"/* ; */ if (insanity->sp >= 99) {\n");
	printLevel(file,level,"/*   */ \tprintf(\"Stack Underflow!\\n\");\n");
	printLevel(file,level,"/*   */ \treturn %s;\n",(isLibrary) ? "false" : "1");
	printLevel(file,level,"/*   */ } else {\n");
	printLevel(file,level,"/*   */ \tvoid* ptr = insanity->stack[++insanity->sp];\n");
	printLevel(file,level,"/*   */ \tif (!ptr) {return %s;} else {goto *ptr;}\n", (isLibrary) ? "true" : "0");
	printLevel(file,level,"/*   */ }\n");
}

void killProgram(FILE* file, bool isLibrary, int level) {
	printLevel(file,level,"/* . */ \treturn %s;\n",(isLibrary) ? "false" : "0");
}


//
// If statements
//
void beginIf(FILE* file, bool isLibrary, int level) {
	printLevel(file,level,"/* { */ if (insanity->compare) {\n");
}

void endIf(FILE* file, bool isLibrary, int level) {
	printLevel(file,level,"/* } */ }\n");
}


//
// Memory Cursors
//
void cursorRight(FILE* file, bool isLibrary, int level) {
	printLevel(file,level,"/* > */ CLAMP(insanity->mc,0,999);\n");
	printLevel(file,level,"/*   */ if (insanity->mc < 999) {++insanity->mc;}\n");
}

void cursorLeft(FILE* file, bool isLibrary, int level) {
	printLevel(file,level,"/* < */ CLAMP(insanity->mc,0,999);\n");
	printLevel(file,level,"/*   */ if (insanity->mc > 0) {--insanity->mc;}\n");
}

void increase10(FILE* file, bool isLibrary, int level) {
	printLevel(file,level,"/* \" */ CLAMP(insanity->dig,0,2);\n");
	printLevel(file,level,"/*   */ if (insanity->dig < 2) {++insanity->dig;}\n");
}

void decrease10(FILE* file, bool isLibrary, int level) {
	printLevel(file,level,"/* ' */ CLAMP(insanity->dig,0,2);\n");
	printLevel(file,level,"/*   */ if (insanity->dig > 0) {--insanity->dig;}\n");
}

void resetCursors(FILE* file, bool isLibrary, int level) {
	printLevel(file,level,"/* _ */ insanity->mc = 0;\n");
	printLevel(file,level,"/*   */ insanity->dig = 0;\n");
}


//
// Memory and registers
//
void uploadACC(FILE* file, bool isLibrary, int level) {
	printLevel(file,level,"/* _ */ CLAMP(insanity->mc,0,999);\n");
	printLevel(file,level,"/*   */ insanity->acc = insanity->memory[insanity->mc];\n");
}

void swapMemory(FILE* file, bool isLibrary, int level) {
	printLevel(file,level,"/* | */ CLAMP(insanity->mc,0,999);\n");
	printLevel(file,level,"/*   */ {short temp = insanity->acc;\n");
	printLevel(file,level,"/*   */  insanity->acc = insanity->memory[insanity->mc];\n");
	printLevel(file,level,"/*   */  insanity->memory[insanity->mc] = temp;}\n");
}

void saveBackup(FILE* file, bool isLibrary, int level) {
	printLevel(file,level,"/* $ */ insanity->bak = insanity->acc;\n");
}

void swapBackup(FILE* file, bool isLibrary, int level) {
	printLevel(file,level,"/* ~ */ {short temp = insanity->bak;\n");
	printLevel(file,level,"/*   */  insanity->bak = insanity->acc;\n");
	printLevel(file,level,"/*   */  insanity->acc = temp;}\n");
}


//
// Maths
//
void add(FILE* file, bool isLibrary, int level) {
	printLevel(file,level,"/* + */ CLAMP(insanity->acc,-999,999);\n");
	printLevel(file,level,"/*   */ insanity->acc += DIGIT(insanity->dig);\n");
	printLevel(file,level,"/*   */ TEST_OVERFLOW(insanity,insanity->acc);\n");
	printLevel(file,level,"/*   */ CLAMP(insanity->acc,-999,999);\n");
}

void sub(FILE* file, bool isLibrary, int level) {
	printLevel(file,level,"/* - */ CLAMP(insanity->acc,-999,999);\n");
	printLevel(file,level,"/*   */ insanity->acc -= DIGIT(insanity->dig);\n");
	printLevel(file,level,"/*   */ TEST_OVERFLOW(insanity,insanity->acc);\n");
	printLevel(file,level,"/*   */ CLAMP(insanity->acc,-999,999);\n");
}

void addBackup(FILE* file, bool isLibrary, int level) {
	printLevel(file,level,"/* & */ CLAMP(insanity->acc,-999,999);\n");
	printLevel(file,level,"/*   */ CLAMP(insanity->bak,-999,999);\n");
	printLevel(file,level,"/*   */ insanity->acc += insanity->bak;\n");
	printLevel(file,level,"/*   */ TEST_OVERFLOW(insanity,insanity->acc);\n");
	printLevel(file,level,"/*   */ CLAMP(insanity->acc,-999,999);\n");
}

void negate(FILE* file, bool isLibrary, int level) {
	printLevel(file,level,"/* ` */ CLAMP(insanity->acc,-999,999);\n");
	printLevel(file,level,"/*   */ insanity->acc *= -1;\n");
}

void resetACC(FILE* file, bool isLibrary, int level) {
	printLevel(file,level,"/* @ */ insanity->acc = 0;\n");
}

void randomNumber(FILE* file, bool isLibrary, int level) {
	printLevel(file,level,"/* %% */ insanity->acc = ((rand() % 1999) - 999);\n");
}


//
// Comparisons
//
void EQU(FILE* file, bool isLibrary, int level) {
	printLevel(file,level,"/* = */ insanity->compare = (insanity->acc == 0);\n");
}

void NEQ(FILE* file, bool isLibrary, int level) {
	printLevel(file,level,"/* * */ insanity->compare = (insanity->acc != 0);\n");
}

void GTR(FILE* file, bool isLibrary, int level) {
	printLevel(file,level,"/* / */ insanity->compare = (insanity->acc > 0);\n");
}

void LSS(FILE* file, bool isLibrary, int level) {
	printLevel(file,level,"/* \\ */ insanity->compare = (insanity->acc < 0);\n");
}

void testOverflow(FILE* file, bool isLibrary, int level) {
	printLevel(file,level,"/* ! */ insanity->compare = insanity->overflow;\n");
}


//
// I/O functions
//
void getUserInput(FILE* file, bool isLibrary, int level) {
	printLevel(file,level,"/* ? */ insanity->acc = getUserInput();\n");
}

void outputChar(FILE* file, bool isLibrary, int level) {
	printLevel(file,level,"/* # */ printChar(insanity->acc);\n");
}

void pause(FILE* file, bool isLibrary, int level) {
	printLevel(file,level,"/* , */ pause(insanity);\n");
}
