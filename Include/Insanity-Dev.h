//
// Development header file for Insanity Native Libraryes
//
#ifndef INSANITY_DEVELOPMENT_HEADER
#define INSANITY_DEVELOPMENT_HEADER

#include <stdbool.h>
#include <stddef.h>		/* For size_t */

//Each native library can store it's own set of data
typedef struct LibraryData_t {
	char* key;
	void* value;
} LibraryData_t;


typedef struct Insanity_t {

	//--- Registers ---
	short acc;		// Acumulator
	short bak;		// Backup Register

	//--- Status Flags ---
	bool overflow;	// Overflow status register
	bool compare;	// Compare status register

	//--- Cursors ---
	short mc;		// Memory Cursor
	char dig;		// Digit Cursor (0, 1, or 2)

	//--- Memory ---
	short memory[1000];		// 1000 Memory Slots

	//--- Stack (Implementation) ---
	void* stack[100];		// 100 Stack slots
	short sp;				// Stack pointer (0 to 99)

	//--- Command Line Arguments ---
	int argc;
	char** argv;

	//--- Library Specific Data ---
	LibraryData_t* data;
	size_t dataLen;				// DO NOT MODIFY
	size_t dataAlloc;			// DO NOT MODIFY

} Insanity_t, *pInsanity_t;



//Basic functions for library data
void* getData(pInsanity_t insanity, const char* library);
void setData(pInsanity_t insanity, const char* library, void* data);


#endif	/* Insanity Development Header Included */
