#pragma once
#include "point.h"

struct Rect {
//
//    const struct Point _;
//
//    int x_end, y_end;
    const void *class;
    struct Point *left_down_corner;
    struct Point *right_up_corner;
};


extern const void *Rect;
