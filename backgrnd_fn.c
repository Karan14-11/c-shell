#include "terminal.h"

iv backgrnd_fn(char *arr, int start, iv vals)
{
    char *back_pr = malloc(MaxLimit);
    int i = start;
    int pid;
    vals.ampers=1;
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
        // printf("%d\n",y);

        char *name[] = {
            "/bin/bash",
            "-c",
            for_pr,
            NULL};
        if (fork() == 0)
        {
            setpgid(0, 0);

            execvp(name[0], name);
        }
        else
        {
            pid=y;
                    printf("%d\n", pid);

            wait(NULL);
        }
    }
    else
    {
        // pid = getpid();

        char *name[] = {
            "/bin/bash",
            "-c",
            back_pr,
            NULL};

        wait(NULL);
        setpgid(0, 0);

        execvp(name[0], name);
    }

    vals = add_bg(vals, y, back_pr);
    vals.list = add_node_ll(vals.list, y, back_pr);
    return vals;
}