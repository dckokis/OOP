#ifndef LAB_FABRIC_FABRIC_H
#define LAB_FABRIC_FABRIC_H

int identify_object_name(const char *obj_name);
void *object_create(char *str);
void object_destroy(void *object);
char *parser(FILE *input);

#endif //LAB_FABRIC_FABRIC_H
