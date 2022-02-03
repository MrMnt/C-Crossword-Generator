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
        "AGREE", 
        "DEEPER", 
        "TIME", 
        "TOLD", 
        "DEAL", 
        "FRIDAY", 
        "HOME", 
        "CUTE", 
        "MEAL", 
        "CAME", 
        "KITE", 
        "AMAZED", 
        "HOLD", 
    }; 
    char *grid[] = {
        "1111111111111111", 
        "1111111111111111", 
        "1111111000011111", 
        "1110000111011111", 
        "0110101000001111", 
        "0110101011011011", 
        "0000100001011011", 
        "0111111010000001", 
        "1111000011111011", 
        "1111111011111111", 
    };
    char *solvedGrid[] = {
        "1111111111111111", 
        "1111111111111111", 
        "1111111HOLD11111", 
        "111CUTE111E11111", 
        "K11A1O1AGREE1111", 
        "I11M1L1M11P11M11", 
        "TIME1DEAL1E11E11", 
        "E111111Z1FRIDAY1", 
        "1111HOME11111L11", 
        "1111111D11111111", 
    };

    int dictionaryLen = 13;
    int matrixHeight = 10;
    int matrixWidth = 16;

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