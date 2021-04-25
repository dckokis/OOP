#include <stdio.h>
#include <stdlib.h>
#include "rect.h"
#include "new.h"

static void *Rect_ctor(void *_self, va_list *app) {

    struct Rect *self = (struct Rect *) _self;
    int x = va_arg(*app, int);
    int y = va_arg(*app, int);
    self->left_down_corner_x = x;
    self->left_down_corner_y = y;

//    self->left_down_corner.x = x;
//    self->left_down_corner.y = y;
//    self->left_down_corner.class = Point;

//    self->left_down_corner = new(Point, x, y);

    x = va_arg(*app, int);
    y = va_arg(*app, int);
    self->right_up_corner_x = x;
    self->right_up_corner_y = y;

//    self->right_up_corner.x = x;
//    self->right_up_corner.y = y;
//    self->right_up_corner.class = Point;

//    self->right_up_corner = new(Point, x, y);
    return self;
}

//static void *Rect_dtor(void *_self) {
//    struct Rect *self = (struct Rect*) _self;
//    free(self->right_up_corner);
//    free(self->left_down_corner);
//    return self;
//}

static void Rect_draw(const void *_self) {
    const struct Rect *self = _self;
    printf("rectangle at (%d, %d) and (%d, %d)\n", self->left_down_corner_x, self->left_down_corner_y,
           self->right_up_corner_x, self->right_up_corner_y);

//    printf("rectangle at (%d, %d) and (%d, %d)\n", self->left_down_corner.x, self->left_down_corner.y,
//           self->right_up_corner.x, self->right_up_corner.y);

//    printf("rectangle at (%d, %d) and (%d, %d)\n", self->left_down_corner->x, self->left_down_corner->y,
//           self->right_up_corner->x, self->right_up_corner->y);
}


static const struct Class _Rect = {

        sizeof(struct Rect),

        Rect_ctor,

        0,

//        Rect_dtor,

        Rect_draw
};

const void *Rect = &_Rect;