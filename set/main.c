#define _CRTDBG_MAP_ALLOC
#include <string.h>
#include <assert.h>
#include "set.h"
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

int main()
{
    //Создаем множество с элементами типа KeyValue;
    void *set = set_create(1, hash, equals);
    //Создаем ключ-значение для множества
    const KeyValue keyValue = {"Key-value"};
    const KeyValue keyValue1 = {"Key-valu1"};
    const KeyValue keyValue2 = {"Key-valu2"};
    const KeyValue keyValue3 = {"Key-valu3"};
    const KeyValue keyValue4 = {"Key-valu4"};
    const KeyValue keyValue5 = {"Key-valu5"};
    set = set_init(set, sizeof(KeyValue), hash, equals, NULL);
    assert(set_init(NULL, 8, hash, equals, NULL) == NULL);
    set_erase(set, (size_t) &keyValue, NULL);
    assert(set_contains(set, NULL) == false);
    assert(set_next(set, (size_t) &keyValue) == set_stop(set));
    assert(set_prev(set, (size_t) &keyValue) == set_stop(set));
    assert(set_last(set) == set_stop(set));
    assert(set_first(set) == set_stop(set));
    assert(set_insert(set, NULL) == false);
    assert(set_insert(NULL, &keyValue) == false);
    assert(0 == set_count(set));
    assert(set_stop(set) == set_first(set));
    assert(set_stop(set) == set_last(set));
    assert(set_next(NULL, 2) == set_stop(NULL));
    assert(set_next(set, set_first(set)) == set_stop(set));
    assert(set_next(set, set_last(set)) == set_stop(set));
    assert(set_prev(set, set_first(set)) == set_stop(set));
    assert(set_prev(set, set_last(set)) == set_stop(set));
    assert(set_contains(set, &keyValue) == false);
    assert(set_stop(set) + 1 == set_count(NULL));

    assert(set_insert(set, &keyValue));
    assert(set_count(set) == 1);
    assert(set_first(set) == set_last(set));


    assert(set_insert(set, &keyValue1));
    assert(set_count(set) == 2);
    assert(set_insert(set, &keyValue2));
    assert(set_count(set) == 3);
    assert(set_insert(set, &keyValue3));
    assert(set_count(set) == 4);
    assert(set_insert(set, &keyValue4));
    assert(set_count(set) == 5);
    assert(set_insert(set, &keyValue5));
    assert(set_count(set) == 6);
    set_remove(set, &keyValue,NULL);
    assert(set_count(set) == 5);
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

    // Send all reports to STDOUT
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);

    _CrtDumpMemoryLeaks();


    return 0;

}