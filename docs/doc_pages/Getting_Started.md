@page Getting_Started Getting Started Guide
@tableofcontents

@section getting_started_s0 Includes
To use the library include `crossword.h` and `m_string.h` files. 

If both files are in the same directory, you only need to include `crossword.h`.
~~~~~~~~~~~~~~~.c
#include "crossword.h"
~~~~~~~~~~~~~~~

@section getting_started_s1 Crossword Initialization

To create a crossword there are two options:
1. Call createCrossword() and provide Matrix and Dictionary file names:
    ~~~~~~~~~~~~~~~~~~.c
    Crossword *crossword = createCrossword("dictionary.txt", "matrix.txt");  
    ~~~~~~~~~~~~~~~~~~
    * @p Dictionary and @p Matrix values will be set automatically.

    <br/>
2. Call createCrossword() with NULL argument(s):
    ~~~~~~~~~~~~~~~~~~.c
    Crossword *crossword = createCrossword(NULL, NULL);
    ~~~~~~~~~~~~~~~~~~
    * @p Dictionary and @p Matrix values will have to be set manually (see setDictionary() and setMatrix()).
        
    <br/>

*For dictionary and matrix file creation see @ref getting_started_s2 and @ref getting_started_s3.

<br/>

@section getting_started_s4 Crossword generation
To fill the initialized crossword with a solution, call fillCrossword():
~~~~~~~~~~~~~~~~~~.c
int solved = fillCrossword(crossword);
~~~~~~~~~~~~~~~~~~
<br/>

@section getting_started_s5 Printing Crossword
To print the crossword we only need to print it's Matrix (see @ref getting_started_s7)
~~~~~~~~~~~~~~~~~~.c
printMatrixPretty(crossword->matrix);
~~~~~~~~~~~~~~~~~~

@section getting_started_s6 Printing Dictionary
See printDictionary()

@section getting_started_s7 Printing Matrix
See printMatrix(), printMatrixPretty(), fprintMatrixPretty()

<br/>


@section getting_started_s8 Deallocating memory
Don't forget to free the allocated memory after use(!)

See freeCrossword(), freeDictionary(), freeMatrix()

<br/>




@section getting_started_s2 Dictionary file requirments

As per createDictionaryFromFile() documentation, the file should:
  * Start with the word list (no empty lines before)
  * Each word is written on a seperate line
  * No spaces (if space is not considered part of a word)
  * All words must be uppercase or lowercase

For example:
~~~~~~~~~~~~~~~~~~~~~~.txt
one
two
three
~~~~~~~~~~~~~~~~~~~~~~

@section getting_started_s3 Matrix file requirments

As per createMatrixFromFile() documentation, the file should:
  * Start with the matrix (no empty lines before)
  * Each row is written on a seperate line
  * Should use #EMPTY_CELL or #WALL_CELL values 

For example:
~~~~~~~~~~~~~~~~~~~~~~.txt
10001
11101
00000
~~~~~~~~~~~~~~~~~~~~~~
