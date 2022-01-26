// VU MIF PS group 4 subgroup 2
// Student nr. 2110640
// mantas.vadopalas@mif.stud.vu.lt

#ifndef M_STRING_H
#define M_STRING_H

#include <string.h>
#include <stdlib.h>

struct String {
    char *s;
    int len;
};
typedef struct String String;

String *createString(char *str);
void freeStringMembers(String *string);
void freeString(String *string);
void freeStringArray(String *stringArr, int n);

#endif