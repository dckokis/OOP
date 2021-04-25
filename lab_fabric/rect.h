#pragma once
#include "point.h"

struct Rect {
    const void *class;
    int left_down_corner_x;
    int left_down_corner_y;
    int right_up_corner_x;
    int right_up_corner_y;

//    struct Point left_down_corner;
//    struct Point right_up_corner;

//    struct Point *left_down_corner;
//    struct Point *right_up_corner;
};


extern const void *Rect;
