// VU MIF PS group 4 subgroup 2
// Student nr. 2110640
// mantas.vadopalas@mif.stud.vu.lt

#include "crossword.h"

void freeDictionary(Dictionary *dictionary){
    freeStringArray(dictionary->wordArr, dictionary->len);
    free(dictionary);
}

void freeMatrix(Matrix *matrix){
    freeStringArray(matrix->rowArr, matrix->height);
    free(matrix);
}

void freeCrossWord(Crossword *crossword){
    freeDictionary(&crossword->dictionary);
    freeMatrix(&crossword->grid);
    free(crossword);
}