// VU MIF PS group 4 subgroup 2
// Student nr. 2110640
// mantas.vadopalas@mif.stud.vu.lt

// Include source file, to not have helper methods in final library
// https://stackoverflow.com/questions/3016526/how-to-hide-helper-functions-from-public-api-in-c
#include "m_helper.c"
#include "crossword.h"

static int solveCrossword(Dictionary *d, Matrix *mt, int wordIndex);

// Tested. Works. 
static int isFilled(Matrix *mt){
    for(int y = 0; y < mt->height; ++y)
        for(int x = 0; x < mt->width; ++x)
            if(mt->grid[y][x] == EMPTY_CELL)
                return FALSE;

    return TRUE;
}

// Tested. Works. 
static Matrix *createBackupMatrix(Matrix *mt){
    Matrix *backupMatrix = createMatrix(mt->grid, mt->height, mt->width);
    return backupMatrix;
}
// Tested. Works. 
static void loadBackupMatrix(Matrix *mt, Matrix *backupMatrix){
    for(int i = 0; i < mt->height; ++i){
        strcpy(mt->grid[i], backupMatrix->grid[i]);
    }
}
// Tested. Works. 
static void putWordHorizontally(String word, Matrix *mt, int row, int col){
    memcpy(&(mt->grid[row][col]), word.s, word.len);
    return;
}
// Tested. Works. 
static void putWordVertically(String word, Matrix *mt, int row, int col){
    for(int i = 0; i < word.len; ++i)
        mt->grid[row + i][col] = word.s[i];
    return;
}
// Tested. Works.
static int isLeftCellOccupied(Matrix *mt, int row, int col){
    if((col == 0) || (mt->grid[row][col - 1] == WALL_CELL)){
        return TRUE;
    } else {
        return FALSE;
    }
}
// Tested. Works. 
static int isTopCellOccupied(Matrix *mt, int row, int col){
    if((row == 0) || (mt->grid[row - 1][col] == WALL_CELL)){
        return TRUE;
    } else {
        return FALSE;
    }
}
// Tested. Works. 
static int isRightCellOccupied(String word, Matrix *mt, int row, int col){
    col += word.len; 

    if((col == mt->width) || (mt->grid[row][col] == WALL_CELL)){
        return TRUE;
    } else {
        return FALSE;
    }
}
// Tested. Works. 
static int isBottomCellOccupied(String word, Matrix *mt, int row, int col){
    row += word.len;

    if((row == mt->height) || (mt->grid[row][col] == WALL_CELL)){
        return TRUE;
    } else {
        return FALSE;
    }
}
// Tested. Works. 
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
// Tested. Works. 
static int findSpotForWordHorizontally(String word, Matrix *mt, int *row_, int *col_){

    for(int row = *row_; row < mt->height; ++row){

        for(int col = *col_; col < mt->width; ++col){
            
            // If the word is too long, dont try the other columns, skip to the next row
            if(col + word.len > mt->width)
                break;

            // Skip to the next column
            if(isOkayToAssignCell(word.s[0], mt, row, col) == FALSE)
                continue;

            // Make sure the cell to the left is occupied
            if(isLeftCellOccupied(mt, row, col) == FALSE)
                continue;

            if(isRightCellOccupied(word, mt, row, col) == FALSE)
                continue;

            // Make sure all the other cells dont have conflicts
            int isOkay = TRUE;
            for(int i = 1; i < word.len; ++i){
                if(isOkayToAssignCell(word.s[i], mt, row, col + i) == FALSE){
                    isOkay = FALSE;
                    break;
                }
            }

            // If it passed all the tests, this spot can be tried
            if(isOkay){
                *row_ = row;
                *col_ = col;
                return TRUE;
            }
        }
    }

    return FALSE;
}
// Tested. Works. 
static int findSpotForWordVertically(String word, Matrix *mt, int *row_, int *col_){

    for(int row = *row_; row < mt->height; ++row){

        // If the word is too long, dont try the other rows
        if(row + word.len > mt->height)
            break;

        for(int col = *col_; col < mt->width; ++col){

            // Skip to the next row
            if(isOkayToAssignCell(word.s[0], mt, row, col) == FALSE)
                continue;

            // Make sure the cell to the left is occupied
            if(isTopCellOccupied(mt, row, col) == FALSE)
                continue;

            if(isBottomCellOccupied(word, mt, row, col) == FALSE)
                continue;

            // Make sure all the other cells dont have conflicts
            int isOkay = TRUE;
            for(int i = 1; i < word.len; ++i){
                if(isOkayToAssignCell(word.s[i], mt, row + i, col) == FALSE){
                    isOkay = FALSE;
                    break;
                }
            }

            // If it passed all the tests, this spot can be tried
            if(isOkay){
                *row_ = row;
                *col_ = col;
                return TRUE;
            }

        }

    }

    return FALSE;
}


int fillCrossword(Crossword *cw){
    return solveCrossword(cw->dictionary, cw->matrix, 0);
}
static int solveCrossword(Dictionary *d, Matrix *mt, int wordIndex){
    // If the crossword is filled, means we solved it
    if(isFilled(mt))
        return TRUE;

    // If not, try to solve it

    // For each word not already on the board
    for(int i = wordIndex; i < d->len; ++i){
        String word = d->wordArr[i];

        // Create a snapshot of the grid, so when we change something
        // And it doesn't work out, we can roll back. 
        Matrix *backupMatrix = createBackupMatrix(mt);
        int row = 0, col = 0; 

        // While we can find an empty cell for word horizontally
        while(findSpotForWordHorizontally(word, mt, &row, &col)){
            
            // Try to put the word horizontally
            putWordHorizontally(word, mt, row, col);
            if(solveCrossword(d, mt, i + 1) == TRUE){
                return TRUE;
            } else {
                loadBackupMatrix(mt, backupMatrix);
                col += 1;
            }
            
        }

        // While we can find an empty cell for word verticaally
        row = 0, col = 0;
        while(findSpotForWordVertically(word, mt, &row, &col)){

            // Try to put the word vertically
            putWordVertically(word, mt, row, col);
            if(solveCrossword(d, mt, i + 1) == TRUE){
                return TRUE;
            } else {
                loadBackupMatrix(mt, backupMatrix);
                col += 1;
            }

        }

        freeMatrix(backupMatrix);
    }

    return FALSE;
}


Crossword *createCrossword(char *dictionaryFileName, char *matrixFileName){
    Crossword *cw = calloc(1, sizeof(Crossword));
    
    if(dictionaryFileName != NULL){
        FILE *dfp = openFile(dictionaryFileName, "r");
        setDictionary(cw, createDictionaryFromFile(dfp));
        fclose(dfp);
    }

    if(matrixFileName != NULL){
        FILE *mfp = openFile(matrixFileName, "r");
        setMatrix(cw, createMatrixFromFile(mfp));
        fclose(mfp);
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

Dictionary *createDictionaryFromFile(FILE *fp){
    Dictionary *d = malloc(sizeof(Dictionary));

    d->len = getFileLineCountTillEmptyLine(fp);
    d->wordArr = malloc(d->len * sizeof(String));

    for(int i = 0; i < d->len; ++i){
        String *tmpStr = createString(fgetLine(fp));
        d->wordArr[i] = *tmpStr;
        free(tmpStr);
    }

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

Matrix *createMatrixFromFile(FILE *fp){
    Matrix *mt = malloc(sizeof(Matrix));

    mt->height = getFileLineCountTillEmptyLine(fp);
    mt->width = strlen(fgetLine(fp));
    fseek(fp, 0l, SEEK_SET);

    mt->grid = malloc(mt->height * sizeof(char *));
    for(int i = 0; i < mt->height; ++i){
        mt->grid[i] = fgetLine(fp);
    }

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