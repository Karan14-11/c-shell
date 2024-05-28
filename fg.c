#include "terminal.h"

iv fg_fn(char *str, int start, iv vals)
{
    start += 2;
    char *pid_str = malloc(20);
    while (1)
    {
        if (str[start] == ' ' || str[start] == '\t')
            start++;
        else
            break;
    }
    int cnt = 0;
    while (str[start] != ' ' && str[start] != '\n' && str[start] != '\0')
    {
        pid_str[cnt++] = str[start++];
    }
    pid_str[cnt] = '\0';
    int pid = strtoint(pid_str);
    int status;
    free(pid_str);
    int pidq;
    while (1)
    {
        pidq = waitpid(pid, &status, WNOHANG);
        if (pidq == -1)
        {
            printf("No Such Process Found!\n");
            break;
        }
        if (pidq == 0)
            continue;
        else
            break;
    }
    return vals;
}