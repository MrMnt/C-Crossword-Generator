// VU MIF PS group 4 subgroup 2
// Student nr. 2110640
// mantas.vadopalas@mif.stud.vu.lt

#include "crossword.h"

int main(int argc, char *argv[]){

    Crossword *cd = createCrossword("test_1/dictionary.txt", "test_1/matrix.txt");
    printDictionary(cd->dictionary);
    putchar('\n');
    printMatrix(cd->matrix);

    freeCrossWord(cd);
    return 0;
}