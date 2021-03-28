#include "Parser.h"
#include <stdio.h>

char *by_line_parser(FILE *input) {
    char buffer[1024];
    char* str = fgets(buffer, 1024, input);
    return str;
}