/** @file crossword.h */

// VU MIF PS group 4 subgroup 2
// Student nr. 2110640
// mantas.vadopalas@mif.stud.vu.lt

#ifndef CROSSWORD_H
#define CROSSWORD_H

#include <ctype.h>
#include <stdio.h>
#include "m_string.h"


#define EMPTY_CELL '0' ///< Value used for identifying empty crossword cells
#define WALL_CELL '1'  ///< value used for identifying crossword wall cells


/** @struct Dictionary
 *  Holds an array of words that **could** be used in the crossword
 */
typedef struct {
    String *wordArr; ///< String array for easy word storage
    int len;         ///< Dictionary length
} Dictionary;

/** @struct Matrix
 *  Stores 2d char array representing crossword grid
 * 
 * Matrix is used to store these crossword values: 
 *   * Which cells are empty
 *   * Which cells are walls
 *   * Which cells have (what) values
 */
typedef struct {
    char **grid; ///< 2d array holding crossword cell values
    int width;   ///< Matrix width (number of columns)
    int height;  ///< Matrix height (number of rows)
} Matrix;

/** @struct Crossword
 *  Stores Dictionary and Matrix
 * 
 * @see Dictionary, Matrix
 */
typedef struct {
    Dictionary *dictionary; ///< Stores what words **could** be used for the crossword
    Matrix *matrix;         ///< Stores the actual values of crossword grid
} Crossword;



/** Creates a crossword from dictionary and matrix text files.
 * 
 * @param dictionaryFileName - C string containing the name of the dictionary file to be used
 * @param matrixFileName - C string containing the name of the matrix file to be used
 * 
 * @returns Pointer to the created Crossword
 * 
 * @note @p dictionaryFileName and @p matrixFileName values may be NULL.
 * @see createDictionaryFromFile() and createMatrixFromFile()
 */
Crossword *createCrossword(char *dictionaryFileName, char *matrixFileName);

/** Creates a dictionary from a text file
 *
 * File requirments:
 *   * Should start with the word list (no empty lines before)
 *   * Each word is written on a seperate line
 *   * No spaces (if space is not considered part of a word)
 * 
 * Parsing stops after encountering the first empty line or end of file is reached.
 * 
 * Example:
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ .txt
 * FIRST
 * WORD
 * THIRD
 * FOURTH
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 * @param dictionaryFileName - C string containing the name of the dictionary file to be used
 * 
 * @note Any ASCII character may be used.
 * @note If file can't be found or opened, it is noted in standart output.
 * 
 * @returns Pointer to the created Dictionary. Otherwise, NULL
 * 
 */
Dictionary *createDictionaryFromFile(char * dictionaryFileName);

/** Creates a matrix from a text file
 * 
 * File requirments:
 *   * Should start with the matrix (no empty lines before)
 *   * Each row is written on a seperate line
 *   * Should use #EMPTY_CELL or #WALL_CELL values 
 * 
 * Parsing stops after encountering the first empty line or end of file is reached.
 * Example:
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ .txt
 * 1101111
 * 1101111
 * 0000011
 * 1101011
 * 1111011
 * 1000000
 * 1111011
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 * @param matrixFileName - C string containing the name of the matrix file to be used
 * 
 * @note Any ASCII character may be used.
 * @note If file can't be found or opened, it is noted in standart output.
 * 
 * @returns Pointer to the created Matrix. Otherwise, NULL
 */
Matrix *createMatrixFromFile(char *matrixFileName);



/** Creates a dictionary from word array
 * 
 * @param words - array of C strings
 * @param dlen - dictionary length
 * 
 * @warning Expects @p words nog to be NULL
 * 
 * @returns Pointer to the created Dictionary
 * 
 */
Dictionary *createDictionary(char **words, int dlen);

/** Creates a matrix from word array
 * 
 * @param grid - (dynamic) 2d array holding crossword cell values
 * @param height - grid  height
 * @param width - grid width
 * 
 * @warning Expects @p grid not to be NULL
 * 
 * @returns Pointer to the created Matrix
 * 
 */
Matrix *createMatrix(char **grid, int height, int width);



/** Finds a possible solution to the crossword
 * 
 * Tries to fill the crossword @p matrix with the words from the @p dictionary
 * 
 * @param cw - pointer to the Crossword which will be solved
 * 
 * @returns 1 (TRUE) if the solution was found, 0 (FALSE) otherwise.
 * 
 */
int fillCrossword(Crossword *cw);



/** Replaces the existing crossword dictionary with a new one
 * 
 * @param cw - pointer to the crossword which dictionary will be set
 * @param d - pointer to the new dictionary
 * 
 * @note Previous dictionary will automatically be deallocated
 * 
 */
void setDictionary(Crossword *cw, Dictionary *d);

/** Replaces the existing crossword matrix with a new one
 * 
 * @param cw - pointer to the Crossword which dictionary will be set
 * @param mt - pointer to the new Matrix
 * 
 * @note Previous matrix will automatically be deallocated
 * 
 */
void setMatrix(Crossword *cw, Matrix *mt);



/** Prints all the words in the dictionary to standart output
 * @param d - pointer to the Dictionary
 */
void printDictionary(Dictionary *d);

/** Prints matrix grid as is to standart output
 * @param mt - pointer to Matrix
 */
void printMatrix(Matrix *mt);

/** Prints formatted matrix grid to standart output
 * @param mt - pointer to Matrix
 */
void printMatrixPretty(Matrix *mt);

/** Prints formatted matrix grid to file
 * @param mt - pointer to Matrix
 */
void fprintMatrixPretty(Matrix *mt, FILE *fp);



/** Deallocates memory used by @p crossword
 * @param crossword - pointer to Crossword that will be deallocated
 * @note @p crossword will be set to NULL
 */
void freeCrossword(Crossword *crossword);

/** Deallocates memory used by @p dictionary
 * @param dictionary - pointer to Dictionary that will be deallocated
 * @note @p dictionary will be set to NULL
 */
void freeDictionary(Dictionary *dictionary);

/** Deallocates memory used by @p matrix
 * @param matrix - pointer to Matrix that will be deallocated
 * @note @p matrix will be set to NULL
 */
void freeMatrix(Matrix *matrix);


#endif