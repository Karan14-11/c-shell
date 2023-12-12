#include "terminal.h"
#include "functions.h"

iv backgrnd_fn(char *arr, int start, iv vals)
{
    char *back_pr = malloc(MaxLimit);
    int i = start;
    int c = 0;
    while (arr[i] != '&')
    {
        back_pr[c++] = arr[i++];
    }
    back_pr[c++] = '\0';
    char *for_pr = malloc(MaxLimit);
    c = 0;
    i++;
    while (arr[i] != '\0' && arr[i] != '\n')
    {
        for_pr[c++] = arr[i++];
    }
    for_pr[c++] = '\0';

    int y = fork();
    if (y != 0)
    {
        printf("%d\n",y);

        char *name[] = {
            "/bin/bash",
            "-c",
            for_pr,
            NULL};
        if (fork() == 0)
        {

            execvp(name[0], name);
        }
        else
        {
            wait(NULL);
        }
    }
    else
    {

        char *name[] = {
            "/bin/bash",
            "-c",
            back_pr,
            NULL};

        wait(NULL);
        execvp(name[0], name);
    }

    vals.list = add_node_ll(vals.list,y,back_pr);
    return vals;
}