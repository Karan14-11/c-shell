#include "terminal.h"

iv ping_fn(char *arr, int start, iv vals)
{
    start += 5;
    char *pid_str = malloc(20);
    while (1)
    {
        if (arr[start] == ' ' || arr[start] == '\t')
            start++;
        else
            break;
    }
    int cnt=0;
    while (arr[start] != ' ')
    pid_str[cnt++]=arr[start++];
    pid_str[cnt++]='\0';
    int pid = strtoint(pid_str);
    while (1)
    {
        if (arr[start] == ' ' || arr[start] == '\t')
            start++;
        else
            break;
    }
    cnt=0;
    while (arr[start] != ' '&&arr[start]!='\n'&&arr[start]!='\0')
    pid_str[cnt++]=arr[start++];
    pid_str[cnt++]='\0';
    int sigval = strtoint(pid_str);
    sigval%=32;
    free(pid_str);
    int a=kill(pid,sigval);
    if(a==-1)
    printf("NO such Process Found!\n");
    return vals;


}