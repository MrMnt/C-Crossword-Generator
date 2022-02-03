// VU MIF PS group 4 subgroup 2
// Student nr. 2110640
// mantas.vadopalas@mif.stud.vu.lt

#include "crossword.h"

void printSuccessMsg(char *msg);

void test_1();
void test_2();
void test_3();
void test_4();

int main(){

    // test_1();
    // test_2();
    test_3();
    // test_4(); // Arranged for BEST scenario

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
    freeCrossword(cw);
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
    freeCrossword(cw);
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
    freeCrossword(cw);
}

void test_4(){
    Crossword *cw = createCrossword(NULL, NULL);

    // Words were added for BEST scenario
    char *words[] = { 
        "blue", 
        "hold", 
        "pie", 
        "cute", 
        "agree", 
        "main", 
        "time", 
        "deal", 
        "Friday", 
        "home", 
        "made", 
        "used", 
        "deeper", 
        "phone", 
        "came", 
        "told", 
        "kite", 
        "amazed", 
        "meal", 
        "shape", 
        "tray", 
    };
    Dictionary *d = createDictionary(words, 21);
    setDictionary(cw, d);

    char *grid[] = {
        "11111111111111110000", 
        "11111111111111111101", 
        "11111110000111110001", 
        "11100001110111110101", 
        "01101010000011110111", 
        "01101010110110000111", 
        "00001000010110110111", 
        "01110110100000011111", 
        "11110000111110111111", 
        "11010110111111111111", 
        "11010111111111111111", 
        "10000111111111111111", 
        "11011111111111111111", 
    };
    Matrix *mt = createMatrix(grid, 13, 20);
    setMatrix(cw, mt);

    fillCrossword(cw);
    printMatrixPretty(cw->matrix);
    freeCrossword(cw);
}

void printSuccessMsg(char *msg){
    printf("[+] %s\n", msg);
}