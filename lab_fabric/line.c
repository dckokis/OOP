#include <stdio.h>
#include <stdlib.h>
#include "line.h"
#include "new.h"

// Объявление конструктора для Line
static void *Line_ctor(void *_self, va_list *app) {

    struct Line *self = (struct Line*) _self;
    int x = va_arg(*app, int);
    int y = va_arg(*app, int);
    self->first = new(Point, x, y);
    x = va_arg(*app, int);
    y = va_arg(*app, int);
    self->second = new(Point, x, y);
    return self;
}

static void * Line_dtor(void *_self) {
    struct Line *self = (struct Line*) _self;
    free(self->first);
    free(self->second);
    return self;
}

//#define x(p) (((const struct Point *)(p)) -> x)
//#define y(p) (((const struct Point *)(p)) -> y)

// Реализация виртуальной функции draw для класса Line
static void Line_draw(const void * _self)
{
    const struct Line *self = _self;

    printf("line through (%d,%d) and (%d, %d)\n", self->first->x, self->first->y,
           self->second->x, self->second->y);
}

// Описание класса Line
static const struct Class _Line = {
        // Размер структуры данных объекта
        sizeof(struct Line),
        // Указатель на функцию-конструктор
        Line_ctor,
        // Деструктор отсутствует
        Line_dtor,
        // Указатель на виртуальную функцию draw
        Line_draw
};

// Объявление глобального указателя на _Line, который и будет представлять
// собой класс Line для пользователей (служить аргументом для функции new).
const void *Line = &_Line;