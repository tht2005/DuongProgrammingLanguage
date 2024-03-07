#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "defs.h"
#include "vector.h"

#include "lexer.h"

int fileLength = 0;
char *fileBuffer = NULL;

void clean() {
	free(fileBuffer);
}

void getFile(const char *fileName) {
	FILE *f = CP(	(void*)fopen(fileName, "rb"),
			"No such file.");

	fseek(f, 0, SEEK_END);
	fileLength = ftell(f);
	fseek(f, 0, SEEK_SET);

	fileBuffer = CP((void*)malloc(fileLength + 5),
			"Out of memory (fileBuffer alloc).");	
	fread(fileBuffer, 1, fileLength, f);

	fclose(f);
}

int main(int argc, char *argv[]) {
	if(argc == 1) {
		printf("\nNo input, use the command ./duong --help to know about commands.\n");
		return 0;
	}
	atexit(clean);
	if(argc == 2) {
		if(strcmp(argv[1], "--help") == 0) {
			getFile("./doc/help.txt");
			printf("\n%s\n", fileBuffer);
			return 0;
		}
		if(strcmp(argv[1], "--version") == 0) {
			printf("\nDuong's compiler, version %s\n", VERSION);
			return 0;
		}
	}

	char *input = NULL, *output = NULL;
	for(int i = 1; i < argc; ++i) {
		if(argv[i][0] == '-') {
			if(strcmp(argv[i], "-o") == 0) {
				if(i + 1 == argc) {
					err("Expect a string after an output flag");
				}
				if(output) {
					err("Too many output files");
				}
				output = argv[i + 1];
				++i;
			}
			else {
				err("Invalid command.");
			}
		}
		else {
			if(input) {
				err("Too many input files");
			}
			input = argv[i];
		}
	}

	// default output name
	if(!output) {
		err("i haven't coded this");
		output = input; //temporary, need to fix later
	}

	getFile(input);

	lexerInit(fileBuffer);

	struct Token *a;
	while((a = getToken())->type != EF) {
		printf("%s %d\n", a->str.arr, a->type);
	}

	return 0;
}

