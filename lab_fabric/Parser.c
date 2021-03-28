#include "Parser.h"
#include <stdio.h>
char *by_line_parser(FILE *input) {
    char buffer[256];
    char *str = fgets(buffer, 256, input);
    return str;
}