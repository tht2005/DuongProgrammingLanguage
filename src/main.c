#include "debug.h"
#include "defs.h"

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

	fileBuffer = CP((void*)malloc(fileLength),
			"Out of memory (fileBuffer alloc).");	
	fread(fileBuffer, 1, fileLength, f);

	fclose(f);
}

int main(int argc, char *argv[]) {
	if(argc == 1) {
		CP(0, "No input.");
	}
	atexit(clean);
	getFile(argv[1]);
	return 0;
}
