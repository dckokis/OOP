#define _CRTDBG_MAP_ALLOC
#include "fabric.h"
#include "new.h"
#include <stdio.h>
#include <crtdbg.h>


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
    char buffer[1024];
    while (!feof (input)) {
        RawStuff *rawStuff = parser(fgets(buffer, 1024, input));
        object = object_create(rawStuff);
        RawStuffDtor(rawStuff);
        draw_object(object);
        delete(object);
    }
    fclose(input);

    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
    _CrtDumpMemoryLeaks();
    return 0;
}