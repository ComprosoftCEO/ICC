#include <Insanity-Dev.h>
#include <stdlib.h>
#include <string.h>


//
// Get library specific data from Insanity object
//
void* getData(pInsanity_t insanity, const char* library) {
	if (!insanity || !library) {return NULL;}

	//Alloc default data
	if (!insanity->data) {
		insanity->data = (LibraryData_t*) malloc(sizeof(LibraryData_t)*10);
		insanity->dataLen = 0;
		insanity->dataAlloc = 10;
	}

	//Do a sequential search
	for (size_t i = 0; i < insanity->dataLen; ++i) {
		if (!strcmp(library,insanity->data[i].key)) {
			return insanity->data[i].value;
		}
	}

	return NULL;	/* Not Found */
}



//
// Set library specific data in the object
//
void setData(pInsanity_t insanity, const char* library, void* data) {
	if (!insanity || !library) {return;}

	//Alloc default data
	if (!insanity->data) {
		insanity->data = (LibraryData_t*) malloc(sizeof(LibraryData_t)*10);
		insanity->dataLen = 0;
		insanity->dataAlloc = 10;
	}

	//Do a sequential search for any existing key
	for (size_t i = 0; i < insanity->dataLen; ++i) {
		if (!strcmp(library,insanity->data[i].key)) {
			insanity->data[i].value = data;
		}
	}

	//Key not found, so resize
	if (insanity->dataLen >= insanity->dataAlloc) {
		insanity->dataAlloc+=10;
		insanity->data = (LibraryData_t*) realloc(insanity->data, sizeof(LibraryData_t) * insanity->dataAlloc);
	}

	//Configure the Key,Value pair
	insanity->data[insanity->dataLen++] = (LibraryData_t) {.key = strdup(library), .value = data};
}
