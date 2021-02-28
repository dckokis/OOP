#include "set.h"
#include <stdlib.h>
#include <stdio.h>

#define MIN_SIZE 10

typedef struct SETITEM {
    const void *data;
} SETITEM;

typedef struct SET {
    size_t itemSize;
    size_t setSize;
    SETITEM *item;
    int *conditions; // empty - 0; full - 1
    size_t (*hash)(const void *);

    bool (*equals)(const void *, const void *);
} SET;

///*Создать новое пустое множество.
///*Размер элемента -- itemSize, для обработки элементов использовать функцию хеширования hash,
///*и функцию проверки на равенство equals.*
void *set_create(size_t itemSize, size_t hash(const void *), bool (*equals)(const void *, const void *)) {
    struct SET *pSet;
    pSet = malloc(sizeof(struct SET));
    if (pSet == NULL) {
        return NULL;
    }
    pSet->itemSize = itemSize;
    pSet->setSize = MIN_SIZE;
    pSet->conditions = malloc(sizeof(pSet->setSize));
    if (pSet->conditions == NULL) {
        printf("Memory allocating error.");
        exit(1);
    }
    for (int  i = 0; i < pSet->setSize; i++) {
        pSet->conditions[i] = 0;
    }
    pSet->hash = hash;
    pSet->equals = equals;

    return pSet;
}

static SETITEM *set_item_create(const void *set) {
    SET const *pSet = set;
    SETITEM *new_item = malloc(pSet->itemSize);
    new_item->data = NULL;
    return new_item;
}

static void *set_destroy_each_item(void *set, void (*destroy)(void *)) {
    SET *pSet = set;
    int i;
    if (destroy == NULL) {
        for (i = 0; i < pSet->setSize; i++) {
            pSet->item[i].data = NULL;
            free(&(pSet->item[i]));
        }
    } else {
        for (i = 0; i < pSet->setSize; i++) {
            (*destroy)(&(pSet->item[i]));
            free(&(pSet->item[i]));
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
    free(pSet->item);
    pSet->setSize = -1;
    free(pSet->item);
    free(set);
}

///*Инициализировать множество новыми параметрами.
///*Если set содержит элементы, то сначала удалить все элементы,
///*потом инициализировать множество с учетом новых параметров.
///*Размер элемента -- itemSize, для обработки элементов использовать функцию хеширования hash,
///*и функцию проверки на равенство equals. Если указана функция destroy, то вызвать её для каждого удаляемого элемента.///
void *set_init(void *set, size_t itemSize, size_t hash(const void *), bool (*equals)(const void *, const void *),
               void (*destroy)(void *)) {
    SET *pSet = set_destroy_each_item(set, destroy);
    pSet->equals = equals;
    pSet->hash = hash;
    pSet->itemSize = itemSize;
    pSet->setSize = MIN_SIZE;
    for (int  i = 0; i < pSet->setSize; i++) {
        pSet->conditions[i] = 0;
    }
    free(pSet->item);
    return pSet;
}

///*Удалить все элементы из множества.
///*Если указана функция destroy,
///*то вызвать её для каждого удаляемого элемента множества.///
void set_clear(void *set, void (*destroy)(void *)) {
    SET *pSet = set_destroy_each_item(set, destroy);
    pSet->setSize = 0;
    free(pSet->item);
    free(pSet->conditions);
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
        } else if (pSet->conditions == 0) {
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
    SETITEM const *pItem = item;
    size_t hash = pSet->hash(pItem->data) % pSet->setSize;
    int i;
    for (i = 0; i < pSet->setSize - hash; i++) {
        if (pSet->conditions[hash + i] == 0) {
            return false;
        } else {
            if (pSet->equals(pSet->item[hash + i].data, pItem->data) == true) {
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
    SETITEM const *pItem = item;
    size_t insert_id = pSet->hash(pItem->data) % pSet->setSize;
    for (int i = 0; i < pSet->setSize - insert_id; i++) {
        if (pSet->conditions[insert_id + i] == 1) {
            if (pSet->item[insert_id + i].data == NULL) {
                pSet->item[insert_id + i].data = pItem->data;
                return true;
            } else {
                if (pSet->equals(pSet->item[insert_id + i].data, pItem->data) == true)
                    return false;
                else if (pSet->equals(pSet->item[insert_id + i].data, pItem->data) == false)
                    continue;
            }
        } else if (pSet->conditions[insert_id + i] == 0) {
            pSet->item[insert_id +i] = *set_item_create(pSet);
            pSet->conditions[insert_id + i] = 1;
            pSet->item[insert_id +i].data = pItem->data;
            return true;
        }
    }
}

///*Найти элемент и удалить из множества.
///*Если указана функция destroy, то вызвать её для удаляемого элемента setItem.///
void set_remove(void *set, const void *item, void (*destroy)(void *)) {
    SET *pSet = set;
    SETITEM const *pItem = item;
    size_t remove_id = pSet->hash(pItem->data) % pSet->setSize;
    if (pSet->conditions[remove_id] == 1) {
        if (destroy != NULL) {
            (*destroy)(&(pSet->item[remove_id]));
            free(&(pSet->item[remove_id]));
            pSet->conditions[remove_id] = 0;
        } else if (destroy == NULL) {
            pSet->item[remove_id].data = NULL;
            free(&(pSet->item[remove_id]));
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
    size_t item_id = 0;
    for (item_id = 0; item_id < pSet->setSize; item_id++){
        if (pSet->conditions[item_id] != 0) {
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
        if (pSet->conditions[item_id] != 0) {
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
    if (item_id == 0) { //No place after
        return set_stop(pSet);
    }
    for (int i = 0; i < pSet->setSize - item_id; i++) {
        if (pSet->conditions[item_id + i] != 0) {
            return item_id + i;
        } else continue;
    }
    return INVALID;
}

///*По идентификатору текущего элемента получить
///*идентификатор предыдущего элемента множества.*///
size_t set_prev(const void *set, size_t item_id) {
    if (set == NULL) {
        return INVALID;
    }
    SET const *pSet = set;
    if (item_id == pSet->setSize - 1) { //No place before
        return set_stop(pSet);
    }
    for (int i = 0; i < item_id; i++) {
        if (pSet->conditions[item_id - i] != 0) {
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
    return &(pSet->item[item_id]);
}

///*Удаление элемента множества по его идентификатору.
///*Если указана функция destroy, то вызвать её для удаляемого элемента множества.
///*После удаления элемента,
///*идентификаторы любых элементов из этого множества могут стать невалидным.///
void set_erase(void *set, size_t item_id, void (*destroy)(void *)) {
    SET const *pSet = set;
    if (pSet->conditions[item_id] != 0) {
        if (destroy != NULL) {
            (*destroy)(&(pSet->item[item_id]));
            free(&(pSet->item[item_id]));
            pSet->conditions[item_id] = 0;
        } else if (destroy == NULL) {
            pSet->item[item_id].data = NULL;
            free(&(pSet->item[item_id]));
            pSet->conditions[item_id] = 0;
        }
    }
}