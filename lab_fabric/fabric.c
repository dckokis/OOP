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

int identify_object_name(const char *obj_name) {
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
    result->obj_name = identify_object_name(object_name);
//    va_start(result->parameters, result->obj_name);
    char *end;
//    va_arg(result->parameters, int);
    result->x1 = strtol(strtok(NULL, " "), &end, 0);
    result->y1 = strtol(strtok(NULL, " "), &end, 0);
    switch (result->obj_name) {
        case POINT:
            break;
        case CIRCLE:
            result->rad = strtol(strtok(NULL, " "), &end, 0);
            break;
        case LINE:
            result->x2 = strtol(strtok(NULL, " "), &end, 0);
            result->y2 = strtol(strtok(NULL, " "), &end, 0);
            break;
        case RECTANGLE:
            result->x2 = strtol(strtok(NULL, " "), &end, 0);
            result->y2 = strtol(strtok(NULL, " "), &end, 0);
            break;
        case UNDEFINED:
            free(result);
            return NULL;
    }
//    va_end(result->parameters);
    return result;
}

/// можно сделать так: парсить строку прямо тут, в object_create передавать условно структуру с параметрами(имя параметры)
void *object_create(RawStuff *rawStuff) {
    if (rawStuff == NULL) {
        return NULL;
    }
    //creating_shape
    if (rawStuff->obj_name >= POINT && rawStuff->obj_name < SHAPES_AMOUNT) {
        void *shape = NULL;
        switch (rawStuff->obj_name) {
            case POINT:
                shape = new(Point, rawStuff->x1, rawStuff->y1);
                break;
            case CIRCLE:
                shape = new(Circle, rawStuff->x1, rawStuff->y1, rawStuff->rad);
                break;
            case LINE:
                shape = new(Line, rawStuff->x1, rawStuff->y1, rawStuff->x2, rawStuff->y2);
                break;
            case RECTANGLE:
                shape = new(Rect, rawStuff->x1, rawStuff->y1, rawStuff->x2, rawStuff->y2);
                break;
        }
        free(rawStuff);
        return shape;
    }
    return NULL;
}

bool draw_object(void *object) {
    if (object == NULL)
        return false;
    draw(object);
    return true;
}