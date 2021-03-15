#include "draw_object.h"
#include <string.h>
#include <stdio.h>


int main(int argc, char **argv) {
    char file_name[40] = "INPUT.txt";
    //strcpy(file_name, *++argv);
    FILE* input = fopen(file_name, "r");
    draw_object(input);
    fclose(input);
    //getchar();
    return 0;
}