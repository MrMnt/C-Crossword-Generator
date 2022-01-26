// VU MIF PS group 4 subgroup 2
// Student nr. 2110640
// mantas.vadopalas@mif.stud.vu.lt

#ifndef CROSSWORD_H
#define CROSSWORD_H

#include "m_string.h"

struct Dictionary {
    String *wordArr;
    int len;
};
typedef struct Dictionary Dictionary;

struct Matrix {
    String *rowArr;
    int width;
    int height;
};
typedef struct Matrix Matrix;

struct Crossword {
    Dictionary dictionary;
    Matrix grid;
};
typedef struct Crossword Crossword;


void freeDictionary(Dictionary *dictionary);
void freeMatrix(Matrix *matrix);
void freeCrossWord(Crossword *crossword);

#endif