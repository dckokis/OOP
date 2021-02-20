#include "set.h"
#include <stdlib.h>

void* set_create(size_t itemSize, size_t hash(const void*), bool (*equals)(const void*, const void*)) {

    typedef struct SETITEM {
        size_t itemSize;
    }SETITEM;

    typedef struct SET {
        size_t setSize;
        SETITEM item;
        size_t (*hash)(const void *);
        bool (*equals)(const void *, const void *);
    }SET;

    struct SET *set;
    set = malloc(sizeof(SET));
    if (set == NULL) {
        return (void *) INVALID;
    }

    set->item.itemSize == itemSize;
    set->hash == hash;
    set->equals == equals;
    set->setSize == 0;
    return set;
}

void set_destroy(void* set, void (*destroy)(void*)) {

}

void* set_init(void* set, size_t itemSize, size_t hash(const void*), bool (*equals)(const void*, const void*),
               void (*destroy)(void*));
void set_clear(void* set, void (*destroy)(void*));

size_t set_count(const void* set);
bool set_contains(const void* set, const void* item);
bool set_insert(void* set, const void* item);
void set_remove(void* set, const void* item, void (*destroy)(void*));

size_t set_first(const void* set);
size_t set_last(const void* set);
size_t set_next(const void* set, size_t item_id);
size_t set_prev(const void* set, size_t item_id);
size_t set_stop(const void* set);
const void* set_current(const void* set, size_t item_id);
void set_erase(void* set, size_t item_id, void (*destroy)(void*));