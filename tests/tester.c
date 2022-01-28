// VU MIF PS group 4 subgroup 2
// Student nr. 2110640
// mantas.vadopalas@mif.stud.vu.lt

#include "crossword.h"

void printSuccessMsg(char *msg);

void test_1();

int main(){

    test_1();
    printSuccessMsg("Test_1 Passed successfully");

    return 0;
}

void test_1(){
    Crossword *cw = createCrossword(NULL, NULL);

    char *words[] = { "kalnas", "namas", "vanduo", "dama", "rasa", "ola", "mia", "jis", };
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

    printDictionary(cw->dictionary);
    printMatrix(cw->matrix);

    freeCrossWord(cw);
}

void printSuccessMsg(char *msg){
    printf("[+] %s\n", msg);
}