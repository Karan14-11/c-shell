#include "terminal.h"

iv purge_fn(char* str,int start,iv vals)
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

    fno = fopen(b, "w");
    if (!fno)
        perror("");
    else
    {
        char * type = malloc(10);
        type[0]='0';
        type[1]='0';
        type[2]='0';
        type[3]='0';
        type[4]='\0';

        
        fwrite(type, 1, strlen(type), fno);
        free(type);
    }
    fclose(fno);
    fptr = fopen(a,"w");
    fclose(fptr);
    return vals;
}
