
// VU MIF PS group 4 subgroup 2
// Student nr. 2110640
// mantas.vadopalas@mif.stud.vu.lt

#include "crossword.h"

int test_crossword_solved_correctly();

int main(){

    int passed = test_crossword_solved_correctly();

    return passed;
}

int test_crossword_solved_correctly(){
    char *words[] = { 
        "FIRST", 
        "WORD", 
        "THIRD", 
        "FOURTH", 
    };
    char *grid[] = {
        "1101111", 
        "1101111", 
        "0000011", 
        "1101011", 
        "1111011", 
        "1000000", 
        "1111011", 
    };
    char *solvedGrid[] = {
        "11W1111", 
        "11O1111", 
        "FIRST11", 
        "11D1H11", 
        "1111I11", 
        "1FOURTH", 
        "1111D11", 
    };

    int dictionaryLen = 4;
    int matrixHeight = 7;
    int matrixWidth = 7;

    Crossword *cw = createCrossword(NULL, NULL);
    Dictionary *d = createDictionary(words, dictionaryLen);
    Matrix *mt = createMatrix(grid, matrixHeight, matrixWidth);
    Matrix *smt = createMatrix(solvedGrid, matrixHeight, matrixWidth);

    setDictionary(cw, d);
    setMatrix(cw, mt);
    fillCrossword(cw);

    int isError = 0;
    for(int i = 0; i < mt->height; ++i){
        if(memcmp(mt->grid[i], smt->grid[i], mt->width * sizeof(char)) != 0){
            isError = 1;

            printf("Failed on line %d\n", i + 1);
            printMatrixPretty(cw->matrix);  
            printMatrixPretty(smt);  
            break;
        }
    }

    freeCrossword(cw);
    freeMatrix(smt);
    return isError;
}