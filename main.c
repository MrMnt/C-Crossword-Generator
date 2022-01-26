// VU MIF PS group 4 subgroup 2
// Student nr. 2110640
// mantas.vadopalas@mif.stud.vu.lt

#include "m_io.h"
#include "crossword.h"

int main(int argc, char *argv[]){
    FILE *dfp = openFile(argv[1], "r");
    FILE *mfp = openFile(argv[2], "r");

    Crossword *cd = createCrossword(dfp, mfp);
    printMatrix(cd->matrix);
    printDictionary(cd->dictionary);

    fclose(dfp);
    fclose(mfp);
    freeCrossWord(cd);
    return 0;
}