#include <stdio.h>
#include <stdlib.h>
#include "line.h"
#include "new.h"
static void *Line_ctor(void *_self, va_list *app) {
    struct Line *self = (struct Line*) _self;
    int x = va_arg(*app, int);
    int y = va_arg(*app, int);
    self->first.x = x;
    self->first.y = y;
    self->first.class = Point;
    x = va_arg(*app, int);
    y = va_arg(*app, int);
    self->second.x = x;
    self->second.y = y;
    self->second.class = Point;
    return self;
}

static void Line_draw(const void * _self)
{
    const struct Line *self = _self;
    printf("line through (%d,%d) and (%d, %d)\n", self->first.x, self->first.y,
           self->second.x, self->second.y);
}

static const struct Class _Line = {
        sizeof(struct Line),
        Line_ctor,
        0,
        Line_draw
};

const void *Line = &_Line;