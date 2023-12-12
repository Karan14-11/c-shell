#include "terminal.h"
#include "functions.h"

char *readLine(FILE *file)
{

    char *line = malloc(MaxLimit);
    char ch = getc(file);
    int count = 0;

    while ((ch != '\n') && (ch != EOF))
    {
        line[count++] = ch;
        ch = getc(file);
    }
    line[count] = '\0';
    return line;
}