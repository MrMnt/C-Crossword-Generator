// VU MIF PS group 4 subgroup 2
// Student nr. 2110640
// mantas.vadopalas@mif.stud.vu.lt

#ifndef CROSSWORD_H
#define CROSSWORD_H

#include "m_string.h"
#include "m_helper.h"

struct Dictionary {
    String *wordArr;
    int len;
};
typedef struct Dictionary Dictionary;

struct Matrix {
    char **grid;
    int width;
    int height;
};
typedef struct Matrix Matrix;

struct Crossword {
    Dictionary *dictionary;
    Matrix *matrix;
};
typedef struct Crossword Crossword;


void freeDictionary(Dictionary *dictionary);
void freeMatrix(Matrix *matrix);
void freeCrossWord(Crossword *crossword);


Dictionary *createDictionary(char **words, int dlen);
Dictionary *createDictionaryFromFile(FILE *fp);
void setDictionary(Crossword *cd, Dictionary *d);
void printDictionary(Dictionary *d);

Matrix *createMatrix(char **grid, int height, int width);
Matrix *createMatrixFromFile(FILE *fp);
void setMatrix(Crossword *cd, Matrix *mt);
void printMatrix(Matrix *mt);

Crossword *createCrossword(char *dictionaryFileName, char *matrixFileName);


#endif