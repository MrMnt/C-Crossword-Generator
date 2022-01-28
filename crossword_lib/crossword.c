// VU MIF PS group 4 subgroup 2
// Student nr. 2110640
// mantas.vadopalas@mif.stud.vu.lt

// Include source file, to not have helper methods in final library
// https://stackoverflow.com/questions/3016526/how-to-hide-helper-functions-from-public-api-in-c
#include "m_helper.c"
#include "crossword.h"

Crossword *createCrossword(char *dictionaryFileName, char *matrixFileName){
    Crossword *cd = calloc(1, sizeof(Crossword));
    
    if(dictionaryFileName != NULL){
        FILE *dfp = openFile(dictionaryFileName, "r");
        setDictionary(cd, createDictionary(dfp));
        fclose(dfp);
    }

    if(matrixFileName != NULL){
        FILE *mfp = openFile(matrixFileName, "r");
        setMatrix(cd, createMatrix(mfp));
        fclose(mfp);
    }

    return cd;
}

void setDictionary(Crossword *cd, Dictionary *d){
    if(cd->dictionary != NULL){
        freeDictionary(cd->dictionary);
    }

    cd->dictionary = d;
}

void setMatrix(Crossword *cd, Matrix *mt){
    if(cd->matrix != NULL){
        freeMatrix(cd->matrix);
    }
    
    cd->matrix = mt;
}

Dictionary *createDictionary(FILE *fp){
    Dictionary *d = malloc(sizeof(Dictionary));

    d->len = getFileLineCount(fp);
    d->wordArr = malloc(d->len * sizeof(String));

    for(int i = 0; i < d->len; ++i){
        String *tmpStr = createString(fgetLine(fp));
        d->wordArr[i] = *tmpStr;
        free(tmpStr);
    }

    return d;
}

void printDictionary(Dictionary *d){
    for(int i = 0; i < d->len; ++i){
        puts(d->wordArr[i].s);
    }
}

Matrix *createMatrix(FILE *fp){
    Matrix *mt = malloc(sizeof(Matrix));

    mt->height = getFileLineCount(fp);
    mt->width = strlen(fgetLine(fp));
    fseek(fp, 0l, SEEK_SET);

    mt->grid = malloc(mt->height * sizeof(char *));
    for(int i = 0; i < mt->height; ++i){
        mt->grid[i] = fgetLine(fp);
    }

    return mt;
}

void printMatrix(Matrix *mt){
    for(int y = 0; y < mt->height; ++y){
        for(int x = 0; x < mt->width; ++x){
            putchar(mt->grid[y][x]);
        }
        putchar('\n');
    }
}



void freeDictionary(Dictionary *d){
    freeStringArray(d->wordArr, d->len);
    free(d);
}

void freeMatrix(Matrix *mt){
    for(int i = 0; i < mt->height; ++i){
        free(mt->grid[i]);
    }
    free(mt->grid);
    free(mt);
}

void freeCrossWord(Crossword *crossword){
    freeDictionary(crossword->dictionary);
    freeMatrix(crossword->matrix);
    free(crossword);
}