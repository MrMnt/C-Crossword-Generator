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
        "fat", 
        "salt", 
        "heat", 
        "wine", 
        "acid", 
    };
    char *grid[] = {
        "1110101", 
        "1010000", 
        "0000101", 
        "1011101", 
    };
    char *solvedGrid[] = { // Should not be solveable
        "1110101", 
        "1010000", 
        "0000101", 
        "1011101", 
    };

    int dictionaryLen = 5;
    int matrixHeight = 4;
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