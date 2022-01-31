/** @file m_string.h */

// VU MIF PS group 4 subgroup 2
// Student nr. 2110640
// mantas.vadopalas@mif.stud.vu.lt

#ifndef M_STRING_H
#define M_STRING_H

#include <string.h>
#include <stdlib.h>

/** @struct String
 *  Abstraction for C string (char *)
 */
typedef struct {
    char *s; ///< Pointer to a C string
    int len; ///< String length
} String;


/** Returns a pointer to the newly allocated String
 * 
 * @param str - C string to be copied
 * 
 * @returns Pointer to the newly created String
 */
String* createString(char *str);


/** Deallocates memory used by @p string
 * 
 * @param string - pointer to the String that will be deallocated
 * 
 * @note @p string will be set to NULL
 * 
 */
void freeString(String *string);


/** Dellocates memory used by @p stringArr
 * 
 * @param stringArr - pointer to the first String in the array
 * @param n - number of elements in the array
 * 
 * @note All of @p stringArr elements will be deallocated
 * @note @p stringArr will be set to NULL
 * 
 */
void freeStringArray(String *stringArr, int n);

#endif