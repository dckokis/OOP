#include "square.h"
#include "new.h"
#include "rect.h"
static void *Square_ctor(void *_self, va_list *app) {
    struct Square *self = ((const struct Class *)Rect)->ctor(_self, app);
    return self;
}