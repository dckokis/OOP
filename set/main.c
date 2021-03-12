#include <string.h>
#include <assert.h>

#include "set.h"

#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>
typedef struct {
    char name[10];
} KeyValue;

static size_t hash(const void* ptr) {
    const int p = 31;
    const int m = 1e9 + 9;
    size_t hash_value = 0;
    size_t p_pow = 1;

    const KeyValue* keyValue = (const KeyValue*)ptr;

    for (size_t i = 0; i < 10; ++i) {
        const char c = keyValue->name[i];
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }

    return hash_value;
}

static bool equals(const void* lhsp, const void* rhsp) {
    const KeyValue* lhs = (const KeyValue*)lhsp;
    const KeyValue* rhs = (const KeyValue*)rhsp;

    return 0 == strcmp(lhs->name, rhs->name);
}

int main(int argc, char* argv[]) {
    //Создаем множество с элементами типа KeyValue;
    void *set = set_create(1, hash, equals);
    //Создаем ключ-значение для множества
    const KeyValue keyValue = {"Key-value"};
    const KeyValue keyValue1 = {"Key-value1"};
    const KeyValue keyValue2 = {"Key-value2"};
    const KeyValue keyValue3 = {"Key-value3"};
    set = set_init(set, sizeof(KeyValue), hash, equals, NULL);
    assert(set_init(NULL, 8, hash, equals, NULL) == NULL);
    assert(0 == set_count(set));
    assert(set_stop(set) == set_first(set));
    assert(set_stop(set) == set_last(set));
    assert(set_next(set, set_first(set)) == set_stop(set));
    assert(set_next(set, set_last(set)) == set_stop(set));
    assert(set_prev(set, set_first(set)) == set_stop(set));
    assert(set_prev(set, set_last(set)) == set_stop(set));
    assert(set_insert(NULL, &keyValue) == false);
    assert(set_contains(set, &keyValue) == false);
    assert(set_stop(set) + 1 == set_count(NULL));

    set_insert(set, &keyValue);
    set_insert(set, &keyValue1);
    set_insert(set, &keyValue2);
    set_insert(set, &keyValue3);
    assert(set_count(set) == 4);
    set_clear(set, NULL);
    size_t y = set_stop(set);
    size_t x = set_first(set);
    assert(set_stop(set) == set_first(set));
    assert(set_insert(set, NULL) == false);


    //Добавляем ключ-значение
    const bool isCreated = (KeyValue *) set_insert(set, &keyValue);
    assert(true == isCreated);

    assert(true == set_contains(set, &keyValue));
    const KeyValue *item = (const KeyValue *) set_current(set, set_first(set));

    assert(0 == strcmp(item->name, keyValue.name));

    assert(set_last(set) == set_first(set));

    assert(set_next(set, set_first(set)) == set_stop(set));

    set_erase(set, hash(&keyValue), NULL);
    assert(set_contains(set, &keyValue) == false);
    assert(set_count(set) == 0);
    assert(set_count(NULL) == -1);

    set_destroy(set, NULL);
    return 0;
    _CrtDumpMemoryLeaks();
}