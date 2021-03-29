#pragma once

#include <stdbool.h>

typedef struct RawStuff{
    int x1, y1, x2, y2, rad, obj_name;
}RawStuff;

int identify_object_name(const char *obj_name);

void *object_create(RawStuff *rawStuff);

bool draw_object(void *object);

