#include "set.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-conversion"
#define MIN_SIZE 10


typedef struct SET {
    size_t itemSize;
    size_t setSize;
    void **items;
    int *conditions;

    size_t (*hash)(const void *);

    bool (*equals)(const void *, const void *);
} SET;

///*Создать новое пустое множество.
///*Размер элемента -- itemSize, для обработки элементов использовать функцию хеширования hash,
///*и функцию проверки на равенство equals.*
void *set_create(size_t itemSize, size_t hash(const void *), bool (*equals)(const void *, const void *)) {
    struct SET *pSet;
    pSet = malloc(sizeof(struct SET));
    if (pSet == NULL || itemSize == 0 || hash == NULL || equals == NULL) {
        return NULL;
    }
    pSet->itemSize = itemSize;
    pSet->setSize = MIN_SIZE;
    pSet->hash = hash;
    pSet->equals = equals;
    pSet->items = malloc(pSet->setSize * sizeof(size_t));
    if (pSet->items == NULL) {
        return NULL;
    }
    pSet->conditions = malloc(pSet->setSize);
    if (pSet->conditions == NULL) {
        return NULL;
    }
    for (int i = 0; i < pSet->setSize; i++) {
        pSet->conditions[i] = 0;
    }
    return pSet;
}

static void *set_item_create(const void *set) {
    SET const *pSet = set;
    void *new_item = malloc(pSet->itemSize);
    return new_item;
}

static void *set_destroy_each_item(void *set, void (*destroy)(void *)) {
    SET *pSet = set;
    int i;
    if (destroy == NULL) {
        for (i = 0; i < pSet->setSize; i++) {
            if (pSet->conditions[i] == 1) {
                pSet->items[i] = NULL;
                pSet->conditions[i] = 0;
                free(pSet->items[i]);
            } else{
                continue;
            }
        }
    } else {
        for (i = 0; i < pSet->setSize; i++) {
            if (pSet->conditions[i] == 1) {
                (*destroy)(&(pSet->items[i]));
                pSet->conditions[i] = 0;
                free(pSet->items[i]);
            } else {
                continue;
            }
        }
    }
    return pSet;
}

///*Удалить существующее множество.
///*Если указана функция destroy,
///*то вызвать её для каждого удаляемого элемента множества.*///
void set_destroy(void *set, void (*destroy)(void *)) {
    SET *pSet = set_destroy_each_item(set, destroy);
    pSet->equals = NULL;
    pSet->hash = NULL;
    pSet->itemSize = -1;
    free(pSet->items);
    pSet->setSize = -1;
    free(*pSet->conditions);
    free(set);
}

///*Инициализировать множество новыми параметрами.
///*Если set содержит элементы, то сначала удалить все элементы,
///*потом инициализировать множество с учетом новых параметров.
///*Размер элемента -- itemSize, для обработки элементов использовать функцию хеширования hash,
///*и функцию проверки на равенство equals. Если указана функция destroy, то вызвать её для каждого удаляемого элемента.///
void *set_init(void *set, size_t itemSize, size_t hash(const void *), bool (*equals)(const void *, const void *),
               void (*destroy)(void *)) {
    if (set == NULL || itemSize == 0 || hash == NULL || equals == NULL) {
        return NULL;
    }
    SET *pSet = set_destroy_each_item(set, destroy);
    pSet->equals = equals;
    pSet->hash = hash;
    pSet->itemSize = itemSize;
    pSet->setSize = MIN_SIZE;

    void **new_items = realloc(pSet->items, pSet->setSize * sizeof(size_t));
    if (new_items == NULL) {
        return NULL;
    }
    free(pSet->items);
    pSet->items = new_items;

    int *new_conditions = realloc(pSet->conditions, pSet->setSize);
    if (new_conditions == NULL) {
        return NULL;
    }
    free(*pSet->conditions);
    pSet->conditions = new_conditions;

    for (int i = 0; i < pSet->setSize; i++) {
        pSet->conditions[i] = 0;
    }

    return pSet;
}

///*Удалить все элементы из множества.
///*Если указана функция destroy,
///*то вызвать её для каждого удаляемого элемента множества.///
void set_clear(void *set, void (*destroy)(void *)) {
    if (set == NULL) {
        return;
    }
    SET *pSet = set_destroy_each_item(set, destroy);
    for (int i = 0; i < pSet->setSize; i++) {
        pSet->conditions[i] = 0;
    }
}

///*Количество элементов во множестве.
///*В случае, если set равен NULL, возвращает INVALID константу.///
size_t set_count(const void *set) {
    if (set == NULL) {
        return INVALID;
    }
    SET const *pSet = set;
    int i;
    int amount = 0;
    for (i = 0; i < pSet->setSize; i++) {
        if (pSet->conditions[i] == 1) {
            amount++;
        } else if (pSet->conditions[i] == 0) {
            break;
        }
    }
    return amount;
}

///*Проверить наличие во множестве заданного элемента.///
bool set_contains(const void *set, const void *item) {
    if (set == NULL) {
        return NULL;
    }
    SET const *pSet = set;
    size_t contain_id = pSet->hash(item) % pSet->setSize;
    int i;
    for (i = 0; i < pSet->setSize - contain_id; i++) {
        if (pSet->conditions[contain_id + i] == 0) {
            return false;
        } else {
            if (pSet->equals(&pSet->items[contain_id + i], item) == true) {
                return true;
            } else continue;
        }
    }
    return false;
}

///*Добавить новый элемент.
///*В случае успеха, функция возвращает true,
///*если такой элемент уже существует -- false.
bool set_insert(void *set, const void *item) {
    SET *pSet = set;
    size_t insert_id = pSet->hash(item) % pSet->setSize;
    for (int i = 0; i < pSet->setSize - insert_id; i++) {
        if (pSet->conditions[insert_id + i] == 1) {
            if (&pSet->items[insert_id + i] == NULL) {
                memcpy(&pSet->items[insert_id + i], item, pSet->itemSize);
                pSet->conditions[insert_id + i] = 1;
                return true;
            } else {
                if (pSet->equals(&pSet->items[insert_id + i], item) == true)
                    return false;
                else if (pSet->equals(&pSet->items[insert_id + i], item) == false)
                    continue;
            }
        } else if (pSet->conditions[insert_id + i] == 0) {
            pSet->items[insert_id + i] = set_item_create(pSet);
            memcpy(&pSet->items[insert_id + i], item, pSet->itemSize);
            pSet->conditions[insert_id + i] = 1;
            return true;
        }
    }
}

///*Найти элемент и удалить из множества.
///*Если указана функция destroy, то вызвать её для удаляемого элемента setItem.///
void set_remove(void *set, const void *item, void (*destroy)(void *)) {
    SET *pSet = set;
    size_t remove_id = pSet->hash(item) % pSet->setSize;
    if (pSet->conditions[remove_id] == 1) {
        if (destroy != NULL) {
            (*destroy)(&(pSet->items[remove_id]));
            free(pSet->items[remove_id]);
            pSet->conditions[remove_id] = 0;
        } else if (destroy == NULL) {
            pSet->items[remove_id] = NULL;
            free(pSet->items[remove_id]);
            pSet->conditions[remove_id] = 0;
        }
    }
}

///*Идентификатор для первого элемента множества.
///*Идентификатор может стать невалидным при модификации множества.*///
size_t set_first(const void *set) {
    if (set == NULL) {
        return INVALID;
    }
    SET const *pSet = set;
    size_t item_id;
    for (item_id = 0; item_id < pSet->setSize; item_id++) {
        if (pSet->conditions[item_id] == 1) {
            return item_id;
        } else {
            continue;
        }
    }
    return set_stop(pSet);
}

///*Идентификатор для последнего элемента множества.
///*Идентификатор может стать невалидным при модификации множества.*///
size_t set_last(const void *set) {
    if (set == NULL) {
        return (size_t) NULL;
    }
    SET const *pSet = set;
    size_t item_id;
    for (item_id = pSet->setSize - 1; item_id >= 0; item_id--) {
        if (pSet->conditions[item_id] == 1) {
            return item_id;
        } else {
            continue;
        }
    }
    return set_stop(pSet);
}

///*По идентификатору текущего элемента получить
///*идентификатор следующего элемента множества.*///
size_t set_next(const void *set, size_t item_id) {
    if (set == NULL) {
        return INVALID;
    }
    SET const *pSet = set;
    if (item_id == pSet->setSize - 1) { //No place after
        return set_stop(pSet);
    }
    for (int i = 1; i < pSet->setSize - item_id; i++) {
        if (pSet->conditions[item_id + i] == 1) {
            return item_id + i;
        } else continue;
    }
    return set_stop(pSet);
}

///*По идентификатору текущего элемента получить
///*идентификатор предыдущего элемента множества.*///
size_t set_prev(const void *set, size_t item_id) {
    if (set == NULL) {
        return INVALID;
    }
    SET const *pSet = set;
    if (item_id == 0) { //No place before
        return set_stop(pSet);
    }
    for (int i = 0; i < item_id; i++) {
        if (pSet->conditions[item_id - i] == 1) {
            return item_id - i;
        } else continue;
    }
    return INVALID;
}

///*Идентификатор, получаемый при попытке
///*обратиться к элементу за пределами множества.*///
size_t set_stop(const void *set) {
    return INVALID - 1;
}

///*Получить указатель на элемент по его идентификатору.*///
const void *set_current(const void *set, size_t item_id) {
    SET const *pSet = set;
    if (pSet == NULL || item_id >= pSet->setSize || item_id < 0 || pSet->conditions[item_id] == 0) {
        return 0;
    }
    return &(pSet->items[item_id]);
}

///*Удаление элемента множества по его идентификатору.
///*Если указана функция destroy, то вызвать её для удаляемого элемента множества.
///*После удаления элемента,
///*идентификаторы любых элементов из этого множества могут стать невалидным.///
void set_erase(void *set, size_t item_id, void (*destroy)(void *)) {
    SET const *pSet = set;
    if (pSet->conditions[item_id] == 1) {
        if (destroy != NULL) {
            (*destroy)(&(pSet->items[item_id]));
            free(pSet->items[item_id]);
            pSet->conditions[item_id] = 0;
        } else if (destroy == NULL) {
            pSet->items[item_id] = NULL;
            free(pSet->items[item_id]);
            pSet->conditions[item_id] = 0;
        }
    }
}
#pragma clang diagnostic pop