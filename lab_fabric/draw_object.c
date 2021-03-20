#include <stdbool.h>

#include "draw_object.h"
#include "new.h"


bool draw_object(void *object) {
        if (object == NULL)
            return false;
        draw(object);
}