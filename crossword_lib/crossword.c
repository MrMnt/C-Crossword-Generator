// VU MIF PS group 4 subgroup 2
// Student nr. 2110640
// mantas.vadopalas@mif.stud.vu.lt

// Include source file, to not have helper methods in final library
// https://stackoverflow.com/questions/3016526/how-to-hide-helper-functions-from-public-api-in-c
#include "m_helper.c"
#include "crossword.h"



// Helper methods for solving purposes. 
static int solveCrossword(Dictionary *d, Matrix *mt, int wordIndex, int *stRows, int *stCols, int startingPosLen);

static int isFilled(Matrix *mt);
static Matrix *createBackupMatrix(Matrix *mt);
static void loadBackupMatrix(Matrix *mt, Matrix *backupMatrix);
static void putWordHorizontally(String word, Matrix *mt, int row, int col);
static void putWordVertically(String word, Matrix *mt, int row, int col);
static int isLeftCellOccupied(Matrix *mt, int row, int col);
static int isTopCellOccupied(Matrix *mt, int row, int col);
static int isRightCellOccupied(String word, Matrix *mt, int row, int col);
static int isBottomCellOccupied(String word, Matrix *mt, int row, int col);
static int isOkayToAssignCell(char newValue, Matrix *mt, int row, int col);
static int wordCanBePlacedVertically(String word, Matrix *mt, int row, int col);
static int wordCanBePlacedHorizontally(String word, Matrix *mt, int row, int col);
static int findAllPossibleStartingPositions(Matrix *mt, int **stRows, int **stCols);



int fillCrossword(Crossword *cw){
    int *stRows, *stCols;
    int startingPosArrLen = findAllPossibleStartingPositions(cw->matrix, &stRows, &stCols);

    int solved = solveCrossword(cw->dictionary, cw->matrix, 0, stRows, stCols, startingPosArrLen);

    free(stRows);
    free(stCols);

    return solved;
}

Crossword *createCrossword(char *dictionaryFileName, char *matrixFileName){
    Crossword *cw = calloc(1, sizeof(Crossword));
    
    if(dictionaryFileName != NULL){
        setDictionary(cw, createDictionaryFromFile(dictionaryFileName));
    }

    if(matrixFileName != NULL){
        setMatrix(cw, createMatrixFromFile(matrixFileName));
    }

    return cw;
}

void setDictionary(Crossword *cw, Dictionary *d){
    if(cw->dictionary != NULL){
        freeDictionary(cw->dictionary);
    }

    cw->dictionary = d;
}

void setMatrix(Crossword *cw, Matrix *mt){
    if(cw->matrix != NULL){
        freeMatrix(cw->matrix);
    }
    
    cw->matrix = mt;
}


Dictionary *createDictionaryFromFile(char * dictionaryFileName){
    if(dictionaryFileName == NULL)
        return NULL;

    FILE *dfp = openFile(dictionaryFileName, "r");
    Dictionary *d = malloc(sizeof(Dictionary));

    d->len = getFileLineCountTillEmptyLine(dfp);
    d->wordArr = malloc(d->len * sizeof(String));

    for(int i = 0; i < d->len; ++i){
        String *tmpStr = createString(fgetLine(dfp));
        d->wordArr[i] = *tmpStr;
        free(tmpStr);
    }

    fclose(dfp);
    return d;
}

Dictionary *createDictionary(char **words, int dlen){
    Dictionary *d = malloc(sizeof(Dictionary));

    d->len = dlen;
    d->wordArr = malloc(d->len * sizeof(String));

    for(int i = 0; i < d->len; ++i){
        String *tmpStr = createString(words[i]);
        d->wordArr[i] = *tmpStr;
        free(tmpStr);
    }

    return d;
}

void printDictionary(Dictionary *d){
    for(int i = 0; i < d->len; ++i){
        puts(d->wordArr[i].s);
    }
    putchar('\n');
}

Matrix *createMatrixFromFile(char *matrixFileName){
    if(matrixFileName == NULL)
        return NULL;

    FILE *mfp = openFile(matrixFileName, "r");
    Matrix *mt = malloc(sizeof(Matrix));

    mt->height = getFileLineCountTillEmptyLine(mfp);
    mt->width = strlen(fgetLine(mfp));
    fseek(mfp, 0l, SEEK_SET);

    mt->grid = malloc(mt->height * sizeof(char *));
    for(int i = 0; i < mt->height; ++i){
        mt->grid[i] = fgetLine(mfp);
    }

    fclose(mfp);
    return mt;
}

Matrix *createMatrix(char **grid, int height, int width){
    Matrix *mt = malloc(sizeof(Matrix));

    mt->height = height;
    mt->width = width;

    mt->grid = malloc(mt->height * sizeof(char *));
    for(int i = 0; i < mt->height; ++i){
        mt->grid[i] = malloc(sizeof(char) * (width + 1));
        strcpy(mt->grid[i], grid[i]);
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
    putchar('\n');
}

void printMatrixPretty(Matrix *mt){
    fprintMatrixPretty(mt, stdout);
}
void fprintMatrixPretty(Matrix *mt, FILE *fp){
    putc(' ', fp);
    for(int i = 0; i < mt->width; ++i){
        printf("%s", " _ ");
    }
    putc('\n', fp);
    for(int row = 0; row < mt->height; ++row){
        putc('|', fp);
        for(int col = 0; col < mt->width; ++col){
            putc(' ', fp);

            char c = toupper(mt->grid[row][col]);
            if(c == EMPTY_CELL){
                putc(' ', fp);
            } else if (c == WALL_CELL){
                putc('.', fp);
            } else {
                putc(c, fp);
            }

            putc(' ', fp);
        }
        putc('\n', fp);
    }
    putc('\n', fp);
}

void freeDictionary(Dictionary *d){
    freeStringArray(d->wordArr, d->len);
    free(d);
    d = NULL;
}

void freeMatrix(Matrix *mt){
    for(int i = 0; i < mt->height; ++i){
        free(mt->grid[i]);
    }
    free(mt->grid);
    free(mt);
    mt = NULL;
}

void freeCrossword(Crossword *crossword){
    freeDictionary(crossword->dictionary);
    freeMatrix(crossword->matrix);
    free(crossword);
    crossword = NULL;
}

static int isFilled(Matrix *mt){
    for(int y = 0; y < mt->height; ++y)
        for(int x = 0; x < mt->width; ++x)
            if(mt->grid[y][x] == EMPTY_CELL)
                return FALSE;

    return TRUE;
}

static Matrix *createBackupMatrix(Matrix *mt){
    Matrix *backupMatrix = createMatrix(mt->grid, mt->height, mt->width);
    return backupMatrix;
}

static void loadBackupMatrix(Matrix *mt, Matrix *backupMatrix){
    for(int i = 0; i < mt->height; ++i){
        memcpy(mt->grid[i], backupMatrix->grid[i], sizeof(char) * mt->width);
    }
}

static void putWordHorizontally(String word, Matrix *mt, int row, int col){
    memcpy(&(mt->grid[row][col]), word.s, word.len);
    return;
}

static void putWordVertically(String word, Matrix *mt, int row, int col){
    for(int i = 0; i < word.len; ++i)
        mt->grid[row + i][col] = word.s[i];
    return;
}

static int isLeftCellOccupied(Matrix *mt, int row, int col){
    if((col == 0) || (mt->grid[row][col - 1] == WALL_CELL)){
        return TRUE;
    } else {
        return FALSE;
    }
}

static int isTopCellOccupied(Matrix *mt, int row, int col){
    if((row == 0) || (mt->grid[row - 1][col] == WALL_CELL)){
        return TRUE;
    } else {
        return FALSE;
    }
}

static int isRightCellOccupied(String word, Matrix *mt, int row, int col){
    col += word.len; 

    if((col == mt->width) || (mt->grid[row][col] == WALL_CELL)){
        return TRUE;
    } else {
        return FALSE;
    }
}

static int isBottomCellOccupied(String word, Matrix *mt, int row, int col){
    row += word.len;

    if((row == mt->height) || (mt->grid[row][col] == WALL_CELL)){
        return TRUE;
    } else {
        return FALSE;
    }
}

static int isOkayToAssignCell(char newValue, Matrix *mt, int row, int col){
    char prevValue = mt->grid[row][col];

    if(prevValue == WALL_CELL){
        return FALSE;
    }

    if((prevValue != EMPTY_CELL) && (prevValue != newValue)){
        return FALSE;
    }

    return TRUE;
}

static int wordCanBePlacedVertically(String word, Matrix *mt, int row, int col){

    // Make sure word fits
    if(row + word.len > mt->height) 
        return FALSE;

    // Check again, because maybe other word has already put a letter here
    if(!isOkayToAssignCell(word.s[0], mt, row, col)) 
        return FALSE;
    
    if(!isTopCellOccupied(mt, row, col))
        return FALSE;

    // Make sure after the word ends, no other can start
    if(!isBottomCellOccupied(word, mt, row, col)) 
        return FALSE;

    // Make sure there are no conflicts in between
    for(int i = 1; i < word.len; ++i){
        if(!isOkayToAssignCell(word.s[i], mt, row + i, col)){
            return FALSE;
        }
    }

    return TRUE;
}

static int wordCanBePlacedHorizontally(String word, Matrix *mt, int row, int col){

    // Make sure word fits
    if(col + word.len > mt->width) 
        return FALSE;

    // Check again, because maybe other word has already put a letter here
    if(!isOkayToAssignCell(word.s[0], mt, row, col)) 
        return FALSE;

    if(!isLeftCellOccupied(mt, row, col))
        return FALSE;

    // Make sure after the word ends, no other can start
    if(!isRightCellOccupied(word, mt, row, col)) 
        return FALSE;

    // Make sure there are no conflicts in between
    for(int i = 1; i < word.len; ++i){
        if(!isOkayToAssignCell(word.s[i], mt, row, col + i)){
            return FALSE;
        }
    }

    return TRUE;
}

static int findAllPossibleStartingPositions(Matrix *mt, int **stRows, int **stCols){
    *stRows = malloc(sizeof(int) * mt->height * mt->width);
    *stCols = malloc(sizeof(int) * mt->height * mt->width);
    int startingPosArrLen = 0;

    for(int row = 0; row < mt->height; ++row){
        for(int col = 0; col < mt->width; ++col){
            if(!isOkayToAssignCell(' ', mt, row, col))
                continue;

            // if word COULD start here
            if(isLeftCellOccupied(mt, row, col) || isTopCellOccupied(mt, row, col)){
                (*stRows)[startingPosArrLen] = row;
                (*stCols)[startingPosArrLen] = col;
                startingPosArrLen += 1;
            }

        }
    }

    *stRows = realloc(*stRows, sizeof(int) * startingPosArrLen);
    *stCols = realloc(*stCols, sizeof(int) * startingPosArrLen);

    return startingPosArrLen;
}


static int solveCrossword(Dictionary *d, Matrix *mt, int wordIndex, int *stRows, int *stCols, int startingPosLen){
    if(isFilled(mt))
        return TRUE;

    Matrix *backupMatrix = createBackupMatrix(mt);
    for(int i = wordIndex; i < d->len; ++i){
        String word = d->wordArr[i];

        // For every (potential) possible starting location
        // Try solving it
        for(int pos = 0; pos < startingPosLen; ++pos){
            int row = stRows[pos];
            int col = stCols[pos];
            
            // ----------------- HORIZONTAL --------------------
            if(wordCanBePlacedHorizontally(word, mt, row, col)){
                putWordHorizontally(word, mt, row, col);
                if(solveCrossword(d, mt, i + 1, stRows, stCols, startingPosLen) == TRUE){
                    return TRUE;
                } else {
                    loadBackupMatrix(mt, backupMatrix);
                }
            }

            // ----------------- VERTICAL --------------------
            if(wordCanBePlacedVertically(word, mt, row, col)){
                putWordVertically(word, mt, row, col);
                if(solveCrossword(d, mt, i + 1, stRows, stCols, startingPosLen) == TRUE){
                    return TRUE;
                } else {
                    loadBackupMatrix(mt, backupMatrix);
                }
            }
        }

    }

    freeMatrix(backupMatrix);
    return FALSE;
}