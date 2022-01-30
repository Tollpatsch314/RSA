#include "Version.h"
#include "ProgParam.h"
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <exception>


__forceinline void ERROR_MSG(int exit_code, const char* const msg, ...) {
	va_list fargs;
	va_start(fargs, msg);
	vfprintf(stderr, msg, fargs);
	va_end(fargs);
	exit(exit_code);
}

void toupper(char* str) {
	while (*str) {
		if (*str >= 'a' && *str <= 'z') (*str) -= 'a' - 'A';
		str++;
	}
}

void help() {
	printf("\xC9");
	for (uint8_t i = 0; i < 42; i++) printf("\xCD");
	printf("\xBB\n\xBAHELP - CryptoVisualizer-C %s\xBA\n", VERSION_STRING);
	printf("\xC8");
	for (uint8_t i = 0; i < 42; i++) printf("\xCD");
	printf("\xBC\n");
}

int main(int argc, char **argv) {

	static ProgParam params = { 0 };

	help();

	char *prog = *argv;
	if (prog == NULL) ERROR_MSG(-1, "Program didn't found!\n");
	
	argv++;
	if (*argv == NULL) ERROR_MSG(1, "Invalid argument count!\nUsage \"%s -h\" to show help of the usage of this program!", prog);

	char **tmp = argv;
	while(*tmp) toupper(*(tmp++));

	for (; *argv != NULL; argv++) {
		
		if (strcmp("-T", *argv)) {
			argv++;
			if (*argv == NULL) ERROR_MSG(1, "No type given!");
			else if (strcmp("E", *argv)) params.type = PROG_PARAM_TYPE_ENCRYPT;
			else if (strcmp("D", *argv)) params.type = PROG_PARAM_TYPE_DECRYPT;
			else ERROR_MSG(1, "Unknown type: %s, valid types are:\ne ... encrytion\nd ... decryption", *argv);
		}
		else if (strcmp("-TE", *argv)) params.type = PROG_PARAM_TYPE_ENCRYPT;
		else if (strcmp("-TD", *argv)) params.type = PROG_PARAM_TYPE_DECRYPT;
		

	}

	return 0;
}