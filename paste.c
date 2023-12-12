#include "terminal.h"
#include "functions.h"

iv paste_fn(char *str, int start, iv vals)
{
    FILE *fno;
    int aaa = strlen(str);
    str[aaa]='\0';
    start++;
    FILE *fptr;
    char *a = malloc(MaxLimit);
    strcpy(a, vals.start_dir);
    int length = strlen(a);
    a[length] = '/';
    a[length + 1] = 'p';
    a[length + 2] = 'a';
    a[length + 3] = 's';
    a[length + 4] = '.';
    a[length + 5] = 't';
    a[length + 6] = 'x';
    a[length + 7] = 't';
    a[length + 8] = '/';
    a[length + 8] = '\0';

    char *b = malloc(MaxLimit);
    strcpy(b, vals.start_dir);
    int lengthb = strlen(b);
    b[lengthb] = '/';
    b[lengthb + 1] = 'n';
    b[lengthb + 2] = 'o';
    b[lengthb + 3] = 's';
    b[lengthb + 4] = '.';
    b[lengthb + 5] = 't';
    b[lengthb + 6] = 'x';
    b[lengthb + 7] = 't';
    b[lengthb + 8] = '/';
    b[lengthb + 8] = '\0';

    fno = fopen(b, "r");
    if (!fno)
        perror("");

    lv line_val = check_lines(fno);

    fclose(fno);

    char **file_buf = (char **)malloc(sizeof(char *) * 15);
    for (int i = 0; i < 15; i++)
        file_buf[i] = malloc(MaxLimit);
    fptr = fopen(a, "r");
    if (!fptr)
        perror("");
    for (int i = 0; i < line_val.lines_written; i++)
    {
        file_buf[i] = readLine(fptr);
    }
    fclose(fptr);

    if (line_val.lines_written < 15)
    {
        for (int i = 0; i < line_val.lines_written; i++)
            printf("%s\n", file_buf[i]);
    }
    else
    {
        for (int i = line_val.start_line; i < 15; i++)
            printf("%s\n", file_buf[i]);
        for (int i = 0; i < line_val.start_line; i++)
            printf("%s\n", file_buf[i]);
    }
    return vals;
}