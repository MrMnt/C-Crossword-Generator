// VU MIF PS group 4 subgroup 2
// Student nr. 2110640
// mantas.vadopalas@mif.stud.vu.lt

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 64
#define MAX_FILE_NAME_LENGTH 36

#define TRUE 1
#define FALSE 0

static FILE *openFile(char *fileName, char *mode);
static int getFileLineCountTillEmptyLine(FILE *fp);
static char *fgetLine(FILE *fp);

static FILE *openFile(char *fileName, char *mode){
    FILE *file = fopen(fileName, mode);

    if(file == NULL){
        printf("Problem while opening file named \"%s\"\n", fileName);
        // exit(-1);
    }

    return file;
}

static int getFileLineCountTillEmptyLine(FILE *fp){
    int prevPos = ftell(fp);
    int count = 0;
    
    char *str = fgetLine(fp);
    while(strlen(str) != 0){
        free(str);
        count += 1;
        if(feof(fp)){
            break;
        }
        str = fgetLine(fp);
    }

    fseek(fp, prevPos, SEEK_SET);
    return count;
}

static char *fgetLine(FILE *fp){
    char *line = calloc((MAX_LINE_LENGTH + 1), sizeof(char));

    fgets(line, MAX_LINE_LENGTH + 1, fp);
    line[strcspn(line, "\n")] = '\0';

    if(strlen(line) == MAX_LINE_LENGTH){
        puts("Line is too long");
        exit(-1);
    }

    line = realloc(line, strlen(line) + 1);
    return line;
}