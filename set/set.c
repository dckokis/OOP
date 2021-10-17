#include "set.h"
#include <stdlib.h>
#include <vcruntime_string.h>

static const size_t MIN_SIZE = 0;

typedef struct SET {
    size_t itemSize;
    size_t setSize;
    void **items;
    int *conditions;

    size_t (*hash)(const void *);

    bool (*equals)(const void *, const void *);
} SET;

static void *set_resize(void *set, size_t new_setSize) {
    SET *pSet = set;
    void **new_items = calloc(new_setSize, new_setSize * sizeof(size_t));
    if (new_items == NULL) {
        return NULL;
    }
    int *new_conditions = calloc(new_setSize, new_setSize * sizeof(int));
    if (new_conditions == NULL) {
        return NULL;
    }
    if (new_setSize == 0) {
        pSet->setSize = 0;
        set_destroy(pSet, NULL);
        free(pSet->items);
        free(pSet->conditions);
        pSet->items = new_items;
        pSet->conditions = new_conditions;
        return pSet;
    }
    int i;
    size_t clone_id;
    for (i = 0; i < pSet->setSize; i++) {
        clone_id = pSet->hash(pSet->items[i]) % new_setSize;
        if (new_conditions[clone_id] == 0) {
            new_items[clone_id] = pSet->items[i];
            if (pSet->conditions[i] == 1) {
                new_conditions[clone_id] = 1;
            }
        } else if (new_conditions[clone_id] == 1) {
            if (pSet->equals(pSet->items[i], new_items[clone_id]) == false) {
                size_t j;
                for (j = clone_id + 1; j < new_setSize; j++) {
                    if (new_conditions[j] == 0) {
                        new_items[j] = pSet->items[i];
                        if (pSet->conditions[i] == 1) {
                            new_conditions[j] = 1;
                        }
                        break;
                    } else if (new_conditions[j] == 1) {
                        continue;
                    }
                }
                for (j = 0; j < clone_id; j++) {
                    if (new_conditions[j] == 0) {
                        new_items[j] = pSet->items[i];
                        if (pSet->conditions[i] == 1) {
                            new_conditions[j] = 1;
                        }
                        break;
                    } else if (new_conditions[j] == 1) {
                        continue;
                    }
                }
            }
        }
    }
    free(pSet->items);
    free(pSet->conditions);
    pSet->setSize = new_setSize;
    pSet->items = new_items;
    pSet->conditions = new_conditions;
    return pSet;
}

static void *set_item_create(size_t itemSize) {
    if (itemSize == 0) {
        return NULL;
    }
    void *new_item = calloc(1, itemSize);
    if (new_item == NULL) {
        return NULL;
    }
    return new_item;
}

static void set_destroy_each_item(void *set, void (*destroy)(void *)) {
    SET *pSet = set;
    int i;
    for (i = 0; i < pSet->setSize; i++) {
        if (pSet->conditions[i] == 1) {
            if (destroy) {
                destroy(pSet->items[i]);
            }
            free(pSet->items[i]);
            pSet->conditions[i] = 0;
        }
    }
}

static const size_t find_place(const void *set, const void *item) {
    const SET *pSet = set;
    size_t item_id = pSet->hash(item) % pSet->setSize;
    size_t i;
    for (i = item_id; i < pSet->setSize; i++) {
        if (pSet->conditions[i] == 1) {
            if (pSet->equals(pSet->items[i], item) == true) {
                return INVALID;
            } else {
                continue;
            }
        } else if (pSet->conditions[i] == 0) {
            return i;
        }
    }
    for (i = 0; i < item_id; i++) {
        if (pSet->conditions[i] == 1) {
            if (pSet->equals(pSet->items[i], item) == true) {
                return INVALID;
            } else {
                continue;
            }
        } else if (pSet->conditions[i] == 0) {
            return i;
        }
    }
    return set_stop(pSet);
}

///*Создать новое пустое множество.
///*Размер элемента -- itemSize, для обработки элементов использовать функцию хеширования hash,
///*и функцию проверки на равенство equals.*
void *set_create(size_t itemSize, size_t hash(const void *), bool (*equals)(const void *, const void *)) {
    if (itemSize == 0 || hash == NULL || equals == NULL) {
        return NULL;
    }
    SET *pSet;
    pSet = malloc(sizeof(SET));
    if (pSet == NULL) {
        return NULL;
    }
    pSet->itemSize = itemSize;
    pSet->setSize = MIN_SIZE;
    pSet->hash = hash;
    pSet->equals = equals;
    pSet->items = calloc(pSet->setSize, sizeof(size_t));
    if (pSet->items == NULL) {
        return NULL;
    }
    pSet->conditions = calloc(pSet->setSize, sizeof(int));
    if (pSet->conditions == NULL) {
        return NULL;
    }
    return pSet;
}

///*Удалить существующее множество.
///*Если указана функция destroy,
///*то вызвать её для каждого удаляемого элемента множества.*///
void set_destroy(void *set, void (*destroy)(void *)) {
    if (set == NULL) {
        return;
    }
    SET *pSet = set;
    set_destroy_each_item(pSet, destroy);
    pSet->equals = NULL;
    pSet->hash = NULL;
    pSet->itemSize = INVALID;
    pSet->setSize = INVALID;
    free(pSet->items);
    free(pSet->conditions);
    free(pSet);
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
    SET *pSet = set;
    set_destroy_each_item(pSet, destroy);
    free(pSet->items);
    free(pSet->conditions);
    free(pSet);
    pSet = set_create(itemSize, hash, equals);
    return pSet;
}

///*Удалить все элементы из множества.
///*Если указана функция destroy,
///*то вызвать её для каждого удаляемого элемента множества.///
void set_clear(void *set, void (*destroy)(void *)) {
    if (set == NULL) {
        return;
    }
    SET *pSet = set;
    set_destroy_each_item(pSet, destroy);
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
            continue;
        }
    }
    return amount;
}

///*Проверить наличие во множестве заданного элемента.///
bool set_contains(const void *set, const void *item) {
    if (set == NULL || item == NULL) {
        return false;
    }
    SET const *pSet = set;
    if (pSet->setSize == 0) {
        return false;
    }
    size_t contain_id = pSet->hash(item) % pSet->setSize;
    if (contain_id >= pSet->setSize) {
        return false;
    }
    int i;
    for (i = contain_id; i < pSet->setSize; i++) {
        if (pSet->conditions[i] == 1) {
            if (pSet->equals(pSet->items[i], item) == true) {
                return true;
            }
        }
    }
    for (i = 0; i < contain_id; i++) {
        if (pSet->conditions[i] == 1) {
            if (pSet->equals(pSet->items[i], item) == true) {
                return true;
            }
        }
    }
    return false;
}

///*Добавить новый элемент.
///*В случае успеха, функция возвращает true,
///*если такой элемент уже существует -- false.
bool set_insert(void *set, const void *item) {
    if (set == NULL || item == NULL) {
        return false;
    }
    SET *pSet = set;
    if (pSet->setSize == 0) {
        set_resize(set, 2);
    }
    size_t insert_id = find_place(pSet, item);
    if (insert_id == set_stop(pSet)) {
        set = set_resize(set, pSet->setSize * 2);
        return set_insert(pSet, item);
    }
    if (insert_id == INVALID) {
        return false;
    }
    if (pSet->conditions[insert_id] == 0) {
        pSet->items[insert_id] = set_item_create(pSet->itemSize);
        if (pSet->items[insert_id] != NULL) {
            memcpy(pSet->items[insert_id], item, pSet->itemSize);
        } else {
            return false;
        }
        pSet->conditions[insert_id] = 1;
        return true;
    }
}

///*Найти элемент и удалить из множества.
///*Если указана функция destroy, то вызвать её для удаляемого элемента setItem.///
void set_remove(void *set, const void *item, void (*destroy)(void *)) {
    if (set == NULL || item == NULL) {
        return;
    }
    SET *pSet = set;
    if (pSet->setSize == 0) {
        return;
    }
    size_t remove_id = pSet->hash(item) % pSet->setSize;
    if (pSet->conditions[remove_id] == 1) {
        if (destroy) {
            destroy(pSet->items[remove_id]);
        }
        free(pSet->items[remove_id]);
        pSet->conditions[remove_id] = 0;
    }

    if (set_count(pSet) < pSet->setSize / 2 && set_count(pSet) != 0) {
        set = set_resize(pSet, pSet->setSize / 2);
    }
}

///*Идентификатор для первого элемента множества.
///*Идентификатор может стать невалидным при модификации множества.*///
size_t set_first(const void *set) {
    if (set == NULL) {
        return set_stop(set);
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
        return set_stop(set);
    }
    SET const *pSet = set;
    if (pSet->setSize == 0) {
        return set_stop(pSet);
    }
    size_t item_id;
    for (item_id = pSet->setSize - 1; item_id > 0; item_id--) {
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
        return set_stop(set);
    }
    SET const *pSet = set;
    if (pSet->setSize == 0) {
        return set_stop(pSet);
    }
    size_t current_id = item_id % pSet->setSize;
    if (current_id == pSet->setSize - 1) { //No place after
        return set_stop(pSet);
    }
    for (int i = 1; i < pSet->setSize - current_id; i++) {
        if (pSet->conditions[item_id + i] == 1) {
            return current_id + i;
        } else continue;
    }
    return set_stop(pSet);
}

///*По идентификатору текущего элемента получить
///*идентификатор предыдущего элемента множества.*///
size_t set_prev(const void *set, size_t item_id) {
    if (set == NULL) {
        return set_stop(set);
    }
    SET const *pSet = set;
    if (pSet->setSize == 0) {
        return set_stop(pSet);
    }
    size_t current_id = item_id % pSet->setSize;
    if (current_id == 0) { //No place before
        return set_stop(pSet);
    }
    for (int i = 0; i < current_id; i++) {
        if (pSet->conditions[current_id - i] == 1) {
            return current_id - i;
        } else continue;
    }
    return set_stop(pSet);
}

///*Идентификатор, получаемый при попытке
///*обратиться к элементу за пределами множества.*///
size_t set_stop(const void *set) {
    return INVALID - 1;
}

///*Получить указатель на элемент по его идентификатору.*///
const void *set_current(const void *set, size_t item_id) {
    SET const *pSet = set;
    if (pSet == NULL || item_id >= pSet->setSize || pSet->setSize == 0 || pSet->conditions[item_id] == 0) {
        return NULL;
    }
    size_t current_id = item_id % pSet->setSize;
    return (pSet->items[current_id]);
}

///*Удаление элемента множества по его идентификатору.
///*Если указана функция destroy, то вызвать её для удаляемого элемента множества.
///*После удаления элемента,
///*идентификаторы любых элементов из этого множества могут стать невалидным.///
void set_erase(void *set, size_t item_id, void (*destroy)(void *)) {
    if (set == NULL) {
        return;
    }
    SET const *pSet = set;
    if (pSet->setSize == 0) {
        return;
    }
    size_t erase_id = item_id % pSet->setSize;
    if (erase_id > pSet->setSize - 1) {
        return;
    }
    if (pSet->conditions[erase_id] == 1) {
        if (destroy != NULL) {
            destroy(pSet->items[erase_id]);
        }
        free(pSet->items[erase_id]);
        pSet->conditions[erase_id] = 0;
    }
}