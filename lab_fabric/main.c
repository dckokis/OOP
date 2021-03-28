#include "fabric.h"
#include "Parser.h"
#include "new.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc > 2) {
        return 1;
    }
    argv[1] = "INPUT.txt";
    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("FILE ERROR");
        return 1;
    }
    void *object;
    while (!feof (input)) {
        object = object_create(by_line_parser(input));
        draw_object(object);
        delete(object);
    }
    fclose(input);
    return 0;
}