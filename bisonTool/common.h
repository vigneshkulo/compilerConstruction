	#include "uthash.h"

	#define INTEGER		1
	#define BOOLEAN		2
	#define UNDEFINED	3

        /* Hash Table implementation is from "UTHASH" open source code */
        typedef struct {
            char key[30];               /* key (string is WITHIN the structure) */
            int index;
            char* type;
            UT_hash_handle hh;          /* makes this structure hashable */
        } SYMTABLE;
