#include "terminal.h"

iv execute_fn(char* str, int start ,iv vals)
{
    start+=19;
    char* no = malloc(4);
    no[0]=str[start];
    no[1]=str[start+1];

    if(no[1]!='\0'&&no[1]!='\n'&&no[1]!=' ')
    no[2]='\0';
    else if(no[1]=='\n'||no[1]==' ')
    no[1]='\0';
    int num = strtoint(no);
    FILE* fptr;
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

    fptr = fopen(b,"r");
    char* value = readLine(fptr);
    fclose(fptr);
    int startline = strtoint(value);
    startline%=100;
    // printf("%d\nHERE",num);
    startline-=num;
    // startline++;
    startline+=15;
    startline%=15;
    fptr = fopen(a,"r");
    for(int i=0;i<=startline;i++)
    value = readLine(fptr);
    fclose(fptr);
    free(a);
    free(b);
    vals = tokenise(value,vals);
    vals = write_com(value,vals);
    return vals;

}