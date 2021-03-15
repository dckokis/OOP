#include "draw_object.h"
#include <stdio.h>


int main(int argc, char **argv) {
    char file_name[40] = "INPUT.txt";
    FILE* input = fopen(file_name, "r");
    draw_object(input);
    fclose(input);
    return 0;
}