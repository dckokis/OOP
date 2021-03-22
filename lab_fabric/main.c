#include "draw_object.h"
#include "fabric.h"
#include <stdio.h>


int main(int argc, char *argv[]) {
    if (argc > 2) {
        return 1;
    }
    //argv[1] = "INPUT.txt";
    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("FILE ERROR");
        return 1;
    }
    void *object;
    while (parser(input) != NULL) {
        object = object_create(parser(input));
        draw_object(object);
        object_destroy(object);
    }
    fclose(input);
    return 0;
}