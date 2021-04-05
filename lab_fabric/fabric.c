#include <string.h>
#include "new.h"
#include <stdlib.h>
#include "fabric.h"
#include "point.h"
#include "circle.h"
#include "line.h"
#include "rect.h"

enum Shape {
    POINT = 0,
    CIRCLE,
    LINE,
    RECTANGLE,
    SHAPES_AMOUNT,
    UNDEFINED = -1
};

int identify_object_type(const char *obj_name) {
    if (obj_name != NULL) {
        if (strcmp(obj_name, "point") == 0)
            return POINT;
        if (strcmp(obj_name, "circle") == 0)
            return CIRCLE;
        if (strcmp(obj_name, "line") == 0)
            return LINE;
        if (strcmp(obj_name, "rect") == 0)
            return RECTANGLE;
    }
    return UNDEFINED;
}

RawStuff *parser(char *str) {
    RawStuff *result = malloc(sizeof(RawStuff));
    char source[256] = "";
    strcpy_s(source, 256, str);
    char *object_name = strtok(source, " ");
    result->obj_type = identify_object_type(object_name);
    char *end;
    switch (result->obj_type) {
        case POINT:
            result->params = calloc(2, sizeof(int));
            result->params_amount = 2;
            result->params[0] = (void *) strtol(strtok(NULL, " "), &end, 0); //x1
            result->params[1] = (void *) strtol(strtok(NULL, " "), &end, 0); //y1
            break;
        case CIRCLE:
            result->params = calloc(3, sizeof(int));
            result->params_amount = 3;
            result->params[0] = (void *) strtol(strtok(NULL, " "), &end, 0); //x1
            result->params[1] = (void *) strtol(strtok(NULL, " "), &end, 0); //y1
            result->params[2] = (void *) strtol(strtok(NULL, " "), &end, 0); //rad
            break;
        case LINE:
            result->params = calloc(4, sizeof(int));
            result->params_amount = 4;
            result->params[0] = (void *) strtol(strtok(NULL, " "), &end, 0); //x1
            result->params[1] = (void *) strtol(strtok(NULL, " "), &end, 0); //y1
            result->params[2] = (void *) strtol(strtok(NULL, " "), &end, 0); //x2
            result->params[3] = (void *) strtol(strtok(NULL, " "), &end, 0); //y2
            break;
        case RECTANGLE:
            result->params = calloc(4, sizeof(int));
            result->params_amount = 4;
            result->params[0] = (void *) strtol(strtok(NULL, " "), &end, 0); //x1
            result->params[1] = (void *) strtol(strtok(NULL, " "), &end, 0); //y1
            result->params[2] = (void *) strtol(strtok(NULL, " "), &end, 0); //x2
            result->params[3] = (void *) strtol(strtok(NULL, " "), &end, 0); //y2
            break;
        case UNDEFINED:
            free(result);
            return NULL;
        default:
            return NULL;
    }
    return result;
}

void *object_create(RawStuff *rawStuff) {
    if (rawStuff == NULL) {
        return NULL;
    }
    ///creating_shape///
    if (rawStuff->obj_type >= POINT && rawStuff->obj_type < SHAPES_AMOUNT) {
        void *shape = NULL;
        switch (rawStuff->obj_type) {
            case POINT:
                shape = new(Point, rawStuff->params[0], rawStuff->params[1]);
                break;
            case CIRCLE:
                shape = new(Circle, rawStuff->params[0], rawStuff->params[1], rawStuff->params[2]);
                break;
            case LINE:
                shape = new(Line, rawStuff->params[0], rawStuff->params[1], rawStuff->params[2], rawStuff->params[3]);
                break;
            case RECTANGLE:
                shape = new(Rect, rawStuff->params[0], rawStuff->params[1], rawStuff->params[2], rawStuff->params[3]);
                break;
            default:
                return NULL;
        }
        return shape;
    }
    return NULL;
}

void RawStuffDtor(RawStuff *rawStuff) {
    for (int i = 0; i < rawStuff->params_amount; ++i) {
        free(rawStuff->params[i]);
    }
    free(rawStuff->params);
    rawStuff->params_amount = 0;
    rawStuff->obj_type = UNDEFINED;
}

bool draw_object(void *object) {
    if (object == NULL)
        return false;
    draw(object);
    return true;
}