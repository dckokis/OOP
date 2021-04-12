#pragma once

// Для struct Point
#include "point.h"

// Структура объекта класса Line
struct Line {
    const void *class;
    struct Point *first;
    struct Point *second;
//    const struct Point _;
//    int x_end, y_end;
};

// Ссылка на указатель на описание класса Line, объявленный в line.c.
extern const void *Line;