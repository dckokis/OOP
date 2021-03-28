#include <stdio.h>
#include "rect.h"
#include "new.h"

static void *Rect_ctor(void *_self, va_list *app) {

//    struct Rect *self = ((const struct Class *)Point)->ctor(_self, app);
//
//
//    self->x_end = va_arg(*app, int);
//    self->y_end = va_arg(*app, int);
    struct Rect *self = (struct Rect*) _self;
    int x = va_arg(*app, int);
    int y = va_arg(*app, int);
    self->left_down_corner = new(Point, x, y);
    x = va_arg(*app, int);
    y = va_arg(*app, int);
    self->right_up_corner = new(Point, x, y);
    return self;
}

//#define x(p) (((const struct Point *)(p)) -> x)
//#define y(p) (((const struct Point *)(p)) -> y)


static void Rect_draw(const void * _self)
{
    const struct Rect *self = _self;

    printf("rectangle at (%d, %d) and (%d, %d)\n", self->left_down_corner->x, self->left_down_corner->y,
           self->right_up_corner->x, self->right_up_corner->y);
}


static const struct Class _Rect = {

        sizeof(struct Rect),

        Rect_ctor,

        0,

        Rect_draw
};


const void *Rect = &_Rect;