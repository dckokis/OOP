#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "draw_object.h"
#include "point.h"
#include "circle.h"
#include "line.h"
#include "rect.h"
#include "new.h"

int name_check(const char *obj_name) {
    if (strcmp(obj_name, "point") == 0)
        return 0;
    if (strcmp(obj_name, "circle") == 0)
        return 1;
    if (strcmp(obj_name, "line") == 0)
        return 2;
    if (strcmp(obj_name, "rect") == 0)
        return 3;
    return -1;
}

void *define_object(FILE *input) {
    char buff[20];
    if (fscanf(input, "%s", buff) == EOF) return NULL;
    int obj_numb;
    obj_numb = name_check(buff);
    while (obj_numb == -1) {
        if (fscanf(input, "%s", buff) == EOF) return NULL;
        obj_numb = name_check(buff);
    }
    int x1, y1, x2, y2, rad;
    fscanf(input, "%s", buff);
    x1 = atoi(buff);
    fscanf(input, "%s", buff);
    y1 = atoi(buff);

    void *p = NULL;
    if (obj_numb == 0) {
        p = new(Point, x1, y1);
    } else if (obj_numb == 1) {
        fscanf(input, "%s", buff);
        rad = atoi(buff);
        p = new(Circle, x1, y1, rad);
    } else if (obj_numb == 2) {
        fscanf(input, "%s", buff);
        x2 = atoi(buff);
        fscanf(input, "%s", buff);
        y2 = atoi(buff);
        p = new(Line, x1, y1, x2, y2);
    } else if (obj_numb == 3) {
        fscanf(input, "%s", buff);
        x2 = atoi(buff);
        fscanf(input, "%s", buff);
        y2 = atoi(buff);
        p = new(Rect, x1, y1, x2, y2);
    }
    return p;
}

int draw_object(FILE *input) {
    if (input == NULL) {
        printf("FILE ERROR\n");
        return -1;
    }

    void *p;
    while (true) {
        p = define_object(input);
        if (p == NULL)
            return 0;
        draw(p);
        delete(p);

    }
}