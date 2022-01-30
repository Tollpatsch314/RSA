#pragma once
#include <stdint.h>

#define PROG_PARAM_TYPE_ENCRYPT		0b11000000
#define PROG_PARAM_TYPE_DECRYPT		0b01000000
#define PROG_PARAM_TYPE_JSON_DOC	0b00000001
#define PROG_PARAM_TYPE_DECRYPT		0b01000000

typedef struct ProgParam
{
	uint8_t type;
	const char* input_file;
	const char* output_file;
	const char* doc_json;
} ProgParam;