// VU MIF PS group 4 subgroup 2
// Student nr. 2110640
// mantas.vadopalas@mif.stud.vu.lt

#include "crossword.h"

void printSuccessMsg(char *msg);

void test_1();
void test_2();
void test_3();

int main(){

    test_1();
    test_2();
    test_3();

    return 0;
}

void test_1(){
    Crossword *cw = createCrossword(NULL, NULL);

    char *words[] = { 
        "kalnas", 
        "namas", 
        "vanduo", 
        "dama", 
        "rasa", 
        "ola", 
        "mia", 
        "jis", 
    };
    Dictionary *d = createDictionary(words, 8);
    setDictionary(cw, d);

    char *grid[] = {
        "101101", 
        "000000", 
        "101101", 
        "100001", 
        "101011", 
        "100011", 
    };
    Matrix *mt = createMatrix(grid, 6, 6);
    setMatrix(cw, mt);

    fillCrossword(cw);
    printMatrixPretty(cw->matrix);
    freeCrossWord(cw);
}

void test_2(){
    Crossword *cw = createCrossword(NULL, NULL);

    char *words[] = { 
        "fat", 
        "salt", 
        "heat", 
        "wine", 
        "acid", 
    };
    Dictionary *d = createDictionary(words, 5);
    setDictionary(cw, d);

    char *grid[] = {
        "1110101", 
        "1010000", 
        "0000101", 
        "1011101", 
    };
    Matrix *mt = createMatrix(grid, 4, 7);
    setMatrix(cw, mt);

    fillCrossword(cw);
    printMatrixPretty(cw->matrix);
    freeCrossWord(cw);
}

void test_3(){
    Crossword *cw = createCrossword(NULL, NULL);

    char *words[] = { 
        "laba", 
        "ryta", 
        "aha", 
    };
    Dictionary *d = createDictionary(words, 3);
    setDictionary(cw, d);

    char *grid[] = {
        "010", 
        "010", 
        "010", 
        "000", 
    };
    Matrix *mt = createMatrix(grid, 4, 3);
    setMatrix(cw, mt);

    fillCrossword(cw);
    printMatrixPretty(cw->matrix);
    freeCrossWord(cw);
}

void printSuccessMsg(char *msg){
    printf("[+] %s\n", msg);
}