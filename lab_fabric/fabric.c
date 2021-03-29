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

/// можно сделать так: парсить строку прямо тут, в object_create передавать условно структуру с параметрами(имя параметры)
void *object_create(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    const char *separate_symbol = " ";
    char source[256] = "";
    strcpy_s(source, 256, str);
    char *object_name = strtok(source, separate_symbol);
    int obj_numb = identify_object_name(object_name);

    //creating_shape
    if (obj_numb >= POINT && obj_numb < SHAPES_AMOUNT) {
        void *shape = NULL;
        int x1, y1, x2, y2, rad;
        char *end;
        ///можно стртол в отдельную функцию
        x1 = strtol(strtok(NULL, separate_symbol), &end, 0);
        y1 = strtol(strtok(NULL, separate_symbol), &end, 0);
        if (strcmp("", end) != 0 && strcmp("\n", end) != 0) {
            return NULL;
        }
        /// switch case быстрее
        if (obj_numb == POINT) {
            shape = new(Point, x1, y1);
        } else if (obj_numb == CIRCLE) {
            rad = strtol(strtok(NULL, separate_symbol), &end, 0);
            shape = new(Circle, x1, y1, rad);
        } else if (obj_numb == LINE) {
            x2 = strtol(strtok(NULL, separate_symbol), &end, 0);
            y2 = strtol(strtok(NULL, separate_symbol), &end, 0);
            shape = new(Line, x1, y1, x2, y2);
        } else if (obj_numb == RECTANGLE) {
            x2 = strtol(strtok(NULL, separate_symbol), &end, 0);
            y2 = strtol(strtok(NULL, separate_symbol), &end, 0);
            shape = new(Rect, x1, y1, x2, y2);
        }
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