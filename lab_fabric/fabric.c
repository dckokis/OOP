#include <string.h>
#include "new.h"
#include <stdio.h>
#include <stdlib.h>

#include "fabric.h"
#include "point.h"
#include "circle.h"
#include "line.h"
#include "rect.h"


enum Names {
    POINT,
    CIRCLE,
    LINE,
    RECTANGLE,
    UNDEFINED = -1
};

int identify_object_name(const char *obj_name) {
    if (strcmp(obj_name, "point") == 0)
        return POINT;
    if (strcmp(obj_name, "circle") == 0)
        return CIRCLE;
    if (strcmp(obj_name, "line") == 0)
        return LINE;
    if (strcmp(obj_name, "rect") == 0)
        return RECTANGLE;
    return UNDEFINED;
}



char *parser(FILE *input) {
    char *str;
    str = fgets(str, 256, input);
    if (str == NULL) {
        return NULL;
    }
}

void *object_create(char *str) {
//    if (str == NULL) {
//
//    }
     char *separate_symbol = " ";
     char *object_name = strtok(str, separate_symbol);
     int obj_numb = identify_object_name(object_name);

     //creating_shape
     if (obj_numb >= POINT && obj_numb <= RECTANGLE) {
        void *shape = NULL;
        int x1, y1, x2, y2, rad;
        x1 = atoi(strtok(str, separate_symbol));
        y1 = atoi(strtok(str, separate_symbol));
        if (obj_numb == POINT) {
            shape = new(Point, x1, y1);
        } else if (obj_numb == CIRCLE) {
            rad = atoi(strtok(str, separate_symbol));
            shape = new(Circle, x1, y1, rad);
        } else if (obj_numb == LINE) {
            x2 = atoi(strtok(str, separate_symbol));
            y2 = atoi(strtok(str, separate_symbol));
            shape = new(Line, x1, y1, x2, y2);
        } else if (obj_numb == RECTANGLE) {
            x2 = atoi(strtok(str, separate_symbol));
            y2 = atoi(strtok(str, separate_symbol));
            shape = new(Rect, x1, y1, x2, y2);
        }
            return shape;
    }
}


void object_destroy(void *object) {
    delete(object);
}