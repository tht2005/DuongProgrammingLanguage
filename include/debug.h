#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdlib.h>

int CC(int code, const char *msg) {
	if(code < 0) {
		printf("Error: %s\n", msg);
		exit(1);
	}
	return code;
}
void *CP(void *ptr, const char *msg) {
	if(!ptr) {
		printf("Error: %s\n", msg);
		exit(1);
	}
	return ptr;
}

#endif
