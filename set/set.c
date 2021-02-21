#include "set.h"
#include <stdlib.h>

typedef struct SETITEM {
    const void *data;
} SETITEM;

typedef struct SET {
    size_t itemSize;
    size_t setSize;
    SETITEM *item;

    size_t (*hash)(const void *);

    bool (*equals)(const void *, const void *);
} SET;

///*Создать новое пустое множество.
///*Размер элемента -- itemSize, для обработки элементов использовать функцию хеширования hash,
///*и функцию проверки на равенство equals.*
void *set_create(size_t itemSize, size_t hash(const void *), bool (*equals)(const void *, const void *)) {
    if ((itemSize == 0) || (hash == NULL) || (equals == NULL)) {
        return (void *) INVALID;
    }
    struct SET *SET;
    SET = malloc(sizeof(SET));
    if (SET == NULL) {
        return (void *) INVALID;
    }

    SET->hash = hash;
    SET->equals = equals;
    SET->setSize = 0;
    SET->item = calloc(SET->setSize, sizeof(SETITEM));
    return SET;
}

void *_set_destroy_each_item(void *set, void (*destroy)(void *)) {
//    if (set == NULL) {
//        exit(INVALID);
//    }
    SET *SET = set;
    int i;
    if (destroy == NULL) {
        for (i = 0; i < SET->setSize; i++) {
            SET->item[i].data = NULL;
            free(&(SET->item[i]));
        }
    } else {
        for (i = 0; i < SET->setSize; i++) {
            (*destroy)(&(SET->item[i]));
            free(&(SET->item[i]));
        }
    }
    return SET;
}

///*Удалить существующее множество.
///*Если указана функция destroy,
///*то вызвать её для каждого удаляемого элемента множества.*///
void set_destroy(void *set, void (*destroy)(void *)) {
    SET *SET = _set_destroy_each_item(set, destroy);
    SET->equals = NULL;
    SET->hash = NULL;
    SET->itemSize = -1;
    free(SET->item);
    SET->setSize = -1;
    free(set);
}

///*Инициализировать множество новыми параметрами.
///*Если set содержит элементы, то сначала удалить все элементы,
///*потом инициализировать множество с учетом новых параметров.
///*Размер элемента -- itemSize, для обработки элементов использовать функцию хеширования hash,
///*и функцию проверки на равенство equals. Если указана функция destroy, то вызвать её для каждого удаляемого элемента.///
void *set_init(void *set, size_t itemSize, size_t hash(const void *), bool (*equals)(const void *, const void *),
               void (*destroy)(void *)) {
    SET *SET = _set_destroy_each_item(set, destroy);
    SET->equals = equals;
    SET->hash = hash;
    SET->itemSize = itemSize;
    SET->setSize = 0;
    SET->item = realloc(SET->item, SET->itemSize);
    if (SET->item == NULL) {
        return (void *) INVALID;
    }
    return SET;
}

///*Удалить все элементы из множества.
///*Если указана функция destroy,
///*то вызвать её для каждого удаляемого элемента множества.///
void set_clear(void *set, void (*destroy)(void *)) {
    SET *SET = _set_destroy_each_item(set, destroy);
    SET->setSize = 0;
    SET->item = realloc(SET->item, SET->setSize);
}

///*Количество элементов во множестве.
///*В случае, если set равен NULL, возвращает INVALID константу.///
size_t set_count(const void *set) {
    if (set == NULL) {
        return (INVALID);
    }
    SET const *SET = set;
    int i;
    int amount = 0;
    for (i = 0; i < SET->setSize; i++) {
        if (&(SET->item[i]) != NULL) {
            amount += 1;
        } else if (&(SET->item[i]) == NULL) {
            continue;
        }
    }
    return amount;
}

///*Проверить наличие во множестве заданного элемента.///
bool set_contains(const void *set, const void *item) {
    if (set == NULL) {
        return (INVALID);
    }
    SET const *SET = set;
    int i;
    for (i = 0; i < SET->setSize; i++) {
        if (&(SET->item[i]) != NULL) {
            if (SET->item[i].data == item) {
                return true;
            } else continue;
        } else if (&(SET->item[i]) == NULL) {
            continue;
        }
    }
    return false;
}

///*Добавить новый элемент.
///*В случае успеха, функция возвращает true,
///*если такой элемент уже существует -- false.
bool set_insert(void *set, const void *item) {
    SET *SET = set;
    size_t hash = SET->hash(item);
    if (&(SET->item[hash]) != NULL) {
        SET->item[hash].data = item;
        return true;
    } else return false;
}

///*Найти элемент и удалить из множества.
///*Если указана функция destroy, то вызвать её для удаляемого элемента setItem.///
void set_remove(void *set, const void *item, void (*destroy)(void *)) {
    SET *SET = set;
    int i;
    for (i = 0; i < SET->setSize; i++) {
        if (&(SET->item[i]) != NULL) {
            if (SET->item[i].data == item) {
                if (destroy != NULL) {
                    (*destroy)(&(SET->item[i]));
                    free(&(SET->item[i]));
                } else if (destroy == NULL) {
                    SET->item[i].data = NULL;
                    free(&(SET->item[i]));
                }
            } else continue;
        } else continue;
    }
}


///*Идентификатор для первого элемента множества.
///*Идентификатор может стать невалидным при модификации множества.*///
size_t set_first(const void *set);

///*Идентификатор для последнего элемента множества.
///*Идентификатор может стать невалидным при модификации множества.*///
size_t set_last(const void *set);

///*По идентификатору текущего элемента получить
///*идентификатор следующего элемента множества.*///
size_t set_next(const void *set, size_t item_id);

///*По идентификатору текущего элемента получить
///*идентификатор предыдущего элемента множества.*///
size_t set_prev(const void *set, size_t item_id);

///*Идентификатор, получаемый при попытке
///*обратиться к элементу за пределами множества.*///
size_t set_stop(const void *set);

///*Получить указатель на элемент по его идентификатору.*///
const void *set_current(const void *set, size_t item_id);

///*Удаление элемента множества по его идентификатору.
///*Если указана функция destroy, то вызвать её для удаляемого элемента множества.
///*После удаления элемента,
///*идентификаторы любых элементов из этого множества могут стать невалидным.///
void set_erase(void *set, size_t item_id, void (*destroy)(void *));