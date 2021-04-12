#pragma once

#include <stdbool.h>

typedef struct RawStuff{
    enum Shape obj_type;
    int params_amount;
    void **params;
}RawStuff;

void RawStuffDtor(RawStuff *rawStuff);

RawStuff *parser(char *str);

void *object_create(RawStuff *rawStuff);

bool draw_object(void *object);