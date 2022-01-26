// VU MIF PS group 4 subgroup 2
// Student nr. 2110640
// mantas.vadopalas@mif.stud.vu.lt

#ifndef M_IO_H
#define M_IO_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_LINE_LENGTH 64
#define MAX_FILE_NAME_LENGTH 36


FILE *openFile(char *fileName, char *mode);
int getFileLength(FILE *fp);
int getFileLineCount(FILE *fp);

char *fgetLine(FILE *fp);

#endif