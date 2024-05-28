#include "terminal.h"

iv piping_fn(char *arr, iv vals)
{
    int pipeno = 0;
    int ff[pipeno][2];
    char *uk = malloc(MaxLimit);

    int oldin = dup(0);
    int oldout = dup(1);
    int length = strlen(arr);
    for (int i = 0; i < length; i++)
    {
        if (arr[i] == '|')
            pipeno++;
    }
    int pipen[pipeno][2];
    for (int i = 0; i < pipeno; i++)
    {
        if (pipe(pipen[i]) == -1)
            assert(0);
    }
    char *inp = malloc(MaxLimit);
    int c = 0;
    while (1)
    {
        if (arr[c] == '\t' || arr[c] == ' ')
            c++;
        else
            break;
    }
    for (int i = 0; i <= pipeno; i++)
    {

        int cnt = 0;
        while (arr[c] != '|' && arr[c] != '\n')
        {
            inp[cnt++] = arr[c++];
        }
        c++;
        if (cnt == 0)
        {
            perror("Invalid Use of pipe\n");
            break;
        }
        inp[cnt] = '\0';
        if (i == 0)
        {
            dup2(pipen[i][1], 1);
            close(pipen[i][1]);
            vals.pipe = 1;

            // printf("dfghj\n");
            // printf("%d\n",ff[i][1]);
            // exit(EXIT_SUCCESS);
        }
        else if (i == pipeno)
        {

            vals.pipe = 1;
            // dup2(oldout,1);
            // fflush(stdout);
            int y = dup2(pipen[i - 1][0], STDIN_FILENO);
            // char ao= EOF;
            // write(pipen[i-1][1],&ao,1);

            close(pipen[i - 1][0]);

            // close(pipen[i-1][1]);
            // printf(EOF);
            dup2(oldout, 1);
            // printf("%dasdf\n",y);
            // printf("\nHERE\n%s\n",uk);
            // close(0);
            // ff[i - 1][0] = close(pipen[i - 1][0]);gc
            // printf("%d\n",ff[i-1][0]);
            // exit(EXIT_SUCCESS);
            // close(pipen[i-1][0]);
            vals.gl = pipen[i - 1][0];
            // printf("ok%d\n",pipen[i-1][1]);
        }
        else
        {
            vals.pipe = 1;
            // close(pipen[i - 1][1]);
            dup2(pipen[i - 1][0], 0);
            close(pipen[i - 1][0]);
            dup2(pipen[i][1], 1);
            close(pipen[i][1]);
        }

        vals = default_terminal(inp, vals);
        // printf("\n");
        // printf(EOF);
        char o[1];
        o[0] = EOF;
        if (i)
        {
            int you = write(pipen[i - 1][1], o, 1);
            close(pipen[i - 1][1]);
            assert(you);
        }
        // close(pipen[i][1]);
    }
    vals.pipe = 0;

    // fflush(stdout);
    dup2(oldin, 0);
    dup2(oldout, 1);
    return vals;
}