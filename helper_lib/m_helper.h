// VU MIF PS group 4 subgroup 2
// Student nr. 2110640
// mantas.vadopalas@mif.stud.vu.lt

#ifndef M_HELPER_H
#define M_HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 64
#define MAX_FILE_NAME_LENGTH 36


static FILE *openFile(char *fileName, char *mode);
static int getFileLength(FILE *fp);
static int getFileLineCount(FILE *fp);

static char *fgetLine(FILE *fp);

#endif