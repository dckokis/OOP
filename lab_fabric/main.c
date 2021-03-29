#include "fabric.h"
#include "new.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc > 2) {
        return 1;
    }
    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("FILE ERROR");
        return 1;
    }
    void *object;
    char buffer[1024];
    while (!feof (input)) {
        object = object_create(fgets(buffer, 1024, input));
        draw_object(object);
        delete(object);
    }
    fclose(input);
    return 0;
}