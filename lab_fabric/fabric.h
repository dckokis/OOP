#pragma once

#include <stdbool.h>

typedef struct RawStuff{
    enum Shape obj_type;
    void **params;
}RawStuff;

RawStuff *parser(char *str);

int identify_object_type(const char *obj_name);

void *object_create(RawStuff *rawStuff);

bool draw_object(void *object);

