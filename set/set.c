#include "set.h"
#include <stdlib.h>

typedef struct SETITEM {
    size_t item_id;
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
    struct SET *pSet;
    pSet = malloc(sizeof(struct SET));
    if (pSet == NULL) {
        return (void *) INVALID;
    }

    pSet->hash = hash;
    pSet->equals = equals;
    pSet->setSize = 0;
    pSet->item = calloc(pSet->setSize, sizeof(SETITEM));
    if (pSet->item == NULL) {
        return (void *) INVALID;
    }
    return pSet;
}

void *_set_destroy_each_item(void *set, void (*destroy)(void *)) {
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
    SET *pSet = _set_destroy_each_item(set, destroy);
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
    SET *pSet = _set_destroy_each_item(set, destroy);
    pSet->equals = equals;
    pSet->hash = hash;
    pSet->itemSize = itemSize;
    pSet->setSize = 0;
    pSet->item = realloc(pSet->item, pSet->itemSize);
    if (pSet->item == NULL) {
        return (void *) INVALID;
    }
    return pSet;
}

///*Удалить все элементы из множества.
///*Если указана функция destroy,
///*то вызвать её для каждого удаляемого элемента множества.///
void set_clear(void *set, void (*destroy)(void *)) {
    SET *pSet = _set_destroy_each_item(set, destroy);
    pSet->setSize = 0;
    pSet->item = realloc(pSet->item, pSet->setSize);
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
        if (&(pSet->item[i]) != NULL) {
            amount += 1;
        } else if (&(pSet->item[i]) == NULL) {
            break;
        }
    }
    return amount;
}

///*Проверить наличие во множестве заданного элемента.///
bool set_contains(const void *set, const void *item) {
    if (set == NULL) {
        return INVALID;
    }
    SET const *pSet = set;
    SETITEM const *pItem = item;
    size_t hash = pSet->hash(pItem->data);
    int i = 0;
    for (i; i < pSet->setSize; i++) {
        if (pSet->item[i].item_id ==
            hash) { //либо можно так: номер i = hash, тогда быстрый поиск но могут быть коллизии
            return true;
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
    for (int i = 0; i < pSet->setSize; i++) {
        if (&(pSet->item[i]) != NULL && pSet->item[i].data == NULL) {
            pSet->item[i].data = pItem->data;
            pSet->item[i].item_id = pSet->hash(pItem->data);
            return true;
        } else break;
    }
    return false;
}

///*Найти элемент и удалить из множества.
///*Если указана функция destroy, то вызвать её для удаляемого элемента setItem.///
void set_remove(void *set, const void *item, void (*destroy)(void *)) {
    SET *pSet = set;
    SETITEM const *pItem = item;
    size_t item_id = pSet->hash(pItem->data);
    for (int i = 0; i < pSet->setSize; i++) {
        if (pSet->item[i].item_id == item_id && pSet->item[i].data != NULL) {
            if (destroy == NULL) {
                pSet->item[i].data = NULL;
                free(&(pSet->item[i]));
            } else if (destroy != NULL) {}
            (*destroy)(&(pSet->item[i].data));
            free(&(pSet->item[i].data));
        } else break;
    }
}


///*Идентификатор для первого элемента множества.
///*Идентификатор может стать невалидным при модификации множества.*///
size_t set_first(const void *set) {
    if (set == NULL) {
        return INVALID;
    }
    SET const *pSet = set;
    int i = 0;
    while (&(pSet->item[i]) == NULL) {
        i++;
    }
    if (i > pSet->setSize) {
        return INVALID;
    } else {
        return pSet->item[i].item_id;
    }
}

///*Идентификатор для последнего элемента множества.
///*Идентификатор может стать невалидным при модификации множества.*///
size_t set_last(const void *set) {
    if (set == NULL) {
        return INVALID;
    }
    SET const *pSet = set;
    int i = pSet->setSize;
    while (&(pSet->item[i]) == NULL) {
        i--;
    }
    if (i < 0) {
        return INVALID;
    } else {
        return pSet->item[i].item_id;
    }
}

///*По идентификатору текущего элемента получить
///*идентификатор следующего элемента множества.*///
size_t set_next(const void *set, size_t item_id) {
    if (set == NULL) {
        return INVALID;
    }
    SET const *pSet = set;
    int i = 0;
    while (pSet->item[i].item_id != item_id) {
        i++;
    }
    if (i >= pSet->setSize) {
        set_stop(set);
    } else {
        return (size_t) pSet->item[i + 1].item_id;
    }
}

///*По идентификатору текущего элемента получить
///*идентификатор предыдущего элемента множества.*///
size_t set_prev(const void *set, size_t item_id) {
    if (set == NULL) {
        return INVALID;
    }
    SET const *pSet = set;;
    int i = 0;
    while (pSet->item[i].item_id != item_id) {
        i++;
    }
    if (i >= pSet->setSize) {
        set_stop(set);
    } else {
        return pSet->item[i - 1].item_id;
    }
}

///*Идентификатор, получаемый при попытке
///*обратиться к элементу за пределами множества.*///
size_t set_stop(const void *set) {
    SET const *pSet = set;
    return (size_t) (pSet->item[pSet->setSize].data);
}

///*Получить указатель на элемент по его идентификатору.*///
const void *set_current(const void *set, size_t item_id) {
    if (set == NULL) {
        return (const void *) (INVALID);
    }
    SET const *pSet = set;
    int i = 0;
    while (pSet->item[i].item_id != item_id) {
        i++;
    }
    if(i > pSet->setSize) {
        return (const void *) INVALID;
    } else
        return (const void*)(&(pSet->item[i]));
}

///*Удаление элемента множества по его идентификатору.
///*Если указана функция destroy, то вызвать её для удаляемого элемента множества.
///*После удаления элемента,
///*идентификаторы любых элементов из этого множества могут стать невалидным.///
void set_erase(void *set, size_t item_id, void (*destroy)(void *)) {
    SET const *pSet = set;
    int i = 0;
    while (pSet->item[i].item_id != item_id) {
        i++;
    }
    if (destroy == NULL) {
        pSet->item[i].data = NULL;
        free(&(pSet->item[i]));
    } else if (destroy != NULL) {
        (*destroy)(&(pSet->item[i].data));
        free(&(pSet->item[i]));
    }
}