// VU MIF PS group 4 subgroup 2
// Student nr. 2110640
// mantas.vadopalas@mif.stud.vu.lt

#include "m_io.h"

FILE *openFile(char *fileName, char *mode){
    FILE *file = fopen(fileName, mode);

    if(file == NULL){
        printf("Problem while opening file named \"%s\"\n", fileName);
        exit(-1);
    }

    return file;
}

int getFileLength(FILE *fp){
    int prevPos = ftell(fp);

    fseek(fp, 0, SEEK_END);
    int len = ftell(fp);

    fseek(fp, prevPos, SEEK_SET);
    return len;
}

int getFileLineCount(FILE *fp){
    int prevPos = ftell(fp);
    int count = 0;
    char c;
    
    do {
        fscanf(fp, "%*[^\n]");
        c = getc(fp);
        count += 1;
    } while(c != EOF);

    fseek(fp, prevPos, SEEK_SET);
    return count;
}

char *fgetLine(FILE *fp){
    char *line = malloc(sizeof(char) * (MAX_LINE_LENGTH + 1));

    fgets(line, MAX_LINE_LENGTH + 1, fp);
    line[strcspn(line, "\n")] = '\0';

    if(strlen(line) == MAX_LINE_LENGTH){
        puts("Line is too long");
        exit(-1);
    }

    line = realloc(line, strlen(line) + 1);
    return line;
}