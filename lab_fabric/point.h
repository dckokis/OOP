#ifndef __point_h
#define __point_h

struct Point {
    const void *class;
    int x, y; /* координаты */
};

extern const void *Point;

#endif