/*
* krypt.h
*
* Simple key based encryption/decryption of all files within a directory.
*
*/

#ifdef __cplusplus
extern "C" { 
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define PRINT_USAGE		do { printf("Usage: %s [directory] [key]\n", argv[0]); } while(0)
static int is_regular(const char *);
void toggle_all_files_in(const char*, const char*, const char*);

#ifdef __cplusplus
} 
#endif