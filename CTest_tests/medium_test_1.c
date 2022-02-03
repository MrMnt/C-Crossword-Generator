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
        "KALNAS", 
        "NAMAS", 
        "VANDUO", 
        "DAMA", 
        "RASA", 
        "OLA", 
        "MIA", 
        "JIS", 
    };
    char *grid[] = {
        "101101", 
        "000000", 
        "101101", 
        "100001", 
        "101011", 
        "100011", 
    };
    char *solvedGrid[] = {
        "1V11R1", 
        "KALNAS", 
        "1N11S1", 
        "1DAMA1", 
        "1U1I11", 
        "1OLA11", 
    };

    int dictionaryLen = 8;
    int matrixHeight = 6;
    int matrixWidth = 6;

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