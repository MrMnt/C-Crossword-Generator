// VU MIF PS group 4 subgroup 2
// Student nr. 2110640
// mantas.vadopalas@mif.stud.vu.lt

#include "m_string.h"

String *createString(char *str){
    String *string = malloc(sizeof(String));

    if(str != NULL){
        string->len = strlen(str);
        string->s = malloc((string->len + 1) * sizeof(char));
        strcpy(string->s, str);
    }

    return string;
}

void freeStringMembers(String *string){
    free(string->s);
}

void freeString(String *string){
    free(string->s);
    free(string);
    return;
}

void freeStringArray(String *stringArr, int n){
    for(int i = 0; i < n; ++i){
        freeStringMembers(stringArr + i);
    }
    free(stringArr);
}