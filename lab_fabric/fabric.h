#pragma once
#include <stdbool.h>

int identify_object_name(const char *obj_name);
void *object_create(char *str);
bool draw_object(void *object);

