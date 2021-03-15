#ifndef __point_h
#define __point_h

struct Point {
    const void *class;
    int x, y; /* координаты */
};

void move(void *_self, int dx, int dy);

extern const void *Point;

#endif