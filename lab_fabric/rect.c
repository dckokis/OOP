#include <stdio.h>
#include <stdlib.h>
#include "rect.h"
#include "new.h"

static void *Rect_ctor(void *_self, va_list *app) {
    struct Rect *self = (struct Rect *) _self;
    int x = va_arg(*app, int);
    int y = va_arg(*app, int);
    self->left_down_corner.x = x;
    self->left_down_corner.y = y;
    self->left_down_corner.class = Point;
    x = va_arg(*app, int);
    y = va_arg(*app, int);
    self->right_up_corner.x = x;
    self->right_up_corner.y = y;
    self->right_up_corner.class = Point;
    return self;
}

static void Rect_draw(const void *_self) {
    const struct Rect *self = _self;
    printf("rectangle at (%d, %d) and (%d, %d)\n", self->left_down_corner.x, self->left_down_corner.y,
           self->right_up_corner.x, self->right_up_corner.y);
}


static const struct Class _Rect = {
        sizeof(struct Rect),
        Rect_ctor,
        0,
        Rect_draw
};

const void *Rect = &_Rect;