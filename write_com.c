#include "terminal.h"
#include "functions.h"


iv write_com(char *inp, iv vals)
{
    FILE *fno;
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

    if (line_val.lines_written < 15)
    {
        fptr = fopen(a, "a");
        if (!fptr)
            perror("");
        int ok = strlen(inp);
        if (inp[ok - 1] == '\n' || inp[ok - 1] == '\t' || inp[ok - 1] == '\0' || inp[ok - 1] == ' ')
            inp[ok - 1] = '\n';
        else
            inp[ok] = '\n';
        fwrite(inp, 1, strlen(inp), fptr);
        fclose(fptr);

        char *type = malloc(10);
        if (line_val.lines_written < 9)
            type[0] = '0';
        else
            type[0] = '1';
        char g = notoas((line_val.lines_written + 1) % 10);

        type[1] = g;
        type[2] = notoas(line_val.start_line / 10);
        type[3] = notoas(line_val.start_line % 10);
        type[4] = '\0';

        fno = fopen(b, "w");
        if (!fno)
            perror("");
        fwrite(type, 1, strlen(type), fno);
        fclose(fno);
        free(a);
        free(b);
    }
    else
    {
        char **file_buf = (char **)malloc(sizeof(char *) * 15);
        for (int i = 0; i < 15; i++)
            file_buf[i] = malloc(MaxLimit);
        fptr = fopen(a, "r");
        if (!fptr)
            perror("");
        for (int i = 0; i < 15; i++)
        {
            file_buf[i] = readLine(fptr);
        }
        fclose(fptr);
        int o = line_val.start_line;
        strcpy(file_buf[o], inp);
        char *type = malloc(10);
        type[0] = '1';
        type[1] = '5';
        type[2] = notoas((line_val.start_line + 1) / 10);
        type[3] = notoas((line_val.start_line + 1) % 10);
        type[4] = '\0';
        fno = fopen(b, "w");
        fwrite(type, 1, strlen(type), fno);
        fclose(fno);
        fptr = fopen(a, "w");
        if (!fptr)
            perror("");
        for (int i = 0; i < 15; i++)
        {
            if(file_buf[i][strlen(file_buf[i])-1]!='\n')
            file_buf[i][strlen(file_buf[i])]='\n';
            fwrite(file_buf[i], 1, strlen(file_buf[i]) , fptr);
        }

        free(a);
        free(b);
        for (int i = 0; i < 15; i++)
            free(file_buf[i]);
        free(file_buf);
        fclose(fptr);
    }
    return vals;
}