#include "terminal.h"
#include "functions.h"


iv default_terminal(char *arr, iv vals)
{

    int length = strlen(arr);
    int ampersand = 0;
    for (int j = 0; j < length; j++)
    {
        if (arr[j] == '&')
        {
            ampersand = 1;
            break;
        }
    }

    int i = 0;
    int warp = 0;
    int peek = 0;
    int seek = 0;
    int pastevents = 0;
    int purge;
    int proclore = 0;
    int execute = 0;
    while (arr[i] != '\0')
    {
        if (arr[i] == '\t')
        {
            i++;
            continue;
        }
        else if (arr[i] == '\n')
        {
            i++;
            continue;
        }
        else if (arr[i] == ' ')
        {
            i++;
            continue;
        }
        else if (arr[i] == 'w' && arr[i + 1] == 'a' && arr[i + 2] == 'r' && arr[i + 3] == 'p')
        {
            warp = 1;
            break;
        }
        else if (arr[i] == 'e' && arr[i + 1] == 'x' && arr[i + 2] == 'i' && arr[i + 3] == 't')
        {
            vals.exit = 1;
            return vals;
            break;
        }

        else if (arr[i] == 'p' && arr[i + 1] == 'e' && arr[i + 2] == 'e' && arr[i + 3] == 'k')
        {
            peek = 1;
            break;
        }
        else if (arr[i] == 's' && arr[i + 1] == 'e' && arr[i + 2] == 'e' && arr[i + 3] == 'k')
        {
            seek = 1;
            break;
        }
        else if (arr[i] == 'p' && arr[i + 1] == 'a' && arr[i + 2] == 's' && arr[i + 3] == 't' && arr[i + 4] == 'e' && arr[i + 5] == 'v' && arr[i + 6] == 'e' && arr[i + 7] == 'n' && arr[i + 8] == 't' && arr[i + 9] == 's' && arr[i + 10] == ' ' && arr[i + 11] == 'p' && arr[i + 12] == 'u' && arr[i + 13] == 'r' && arr[i + 14] == 'g' && arr[i + 15] == 'e')
        {

            purge = 1;
            break;
        }
        else if (arr[i] == 'p' && arr[i + 1] == 'a' && arr[i + 2] == 's' && arr[i + 3] == 't' && arr[i + 4] == 'e' && arr[i + 5] == 'v' && arr[i + 6] == 'e' && arr[i + 7] == 'n' && arr[i + 8] == 't' && arr[i + 9] == 's' && arr[i + 10] == ' ' && arr[i + 11] == 'e' && arr[i + 12] == 'x' && arr[i + 13] == 'e' && arr[i + 14] == 'c' && arr[i + 15] == 'u' && arr[i + 16] == 't' && arr[i + 17] == 'e')
        {
            execute = 1;
            break;
        }
        else if (arr[i] == 'p' && arr[i + 1] == 'a' && arr[i + 2] == 's' && arr[i + 3] == 't' && arr[i + 4] == 'e' && arr[i + 5] == 'v' && arr[i + 6] == 'e' && arr[i + 7] == 'n' && arr[i + 8] == 't' && arr[i + 9] == 's')
        {
            pastevents = 1;
            vals.pe = 1;
            break;
        }
        else if (arr[i] == 'p' && arr[i + 1] == 'r' && arr[i + 2] == 'o' && arr[i + 3] == 'c' && arr[i + 4] == 'l' && arr[i + 5] == 'o' && arr[i + 6] == 'r' && arr[i + 7] == 'e')
        {
            proclore = 1;
            break;
        }
        else
            break;
    }

    if (warp == 1 && ampersand == 0)
    {
        vals = warp_fn(arr, i, vals);
    }
    else if (peek == 1 && ampersand == 0)
    {
        vals = peek_fn(arr, i, vals);
    }
    else if (seek == 1 && ampersand == 0)
    {
        vals = seek_fn(arr, i, vals);
    }
    else if (purge == 1 && ampersand == 0)
    {
        vals = purge_fn(arr, i, vals);
        vals.pe = 2;
    }
    else if (pastevents == 1 && ampersand == 0)
    {

        vals = paste_fn(arr, i, vals);
        vals.pe = 1;
    }
    else if (proclore == 1)
    {

        vals = proclore_fn(arr, i, vals);
    }
    else if (execute == 1)
    {
        
        vals = execute_fn(arr, i, vals);
        vals.pe=2;
    }
    else
    {
        if (ampersand == 0)
        {
            char *name[] = {
                "/bin/bash",
                "-c",
                arr,
                NULL};
            if (fork() == 0)
                execvp(name[0], name);
            wait(NULL);
        }
        else
        {
            vals = backgrnd_fn(arr, i, vals);
        }
    }
    if (arr[i] == 's' && arr[i + 1] == 'l' && arr[i + 2] == 'e' && arr[i + 3] == 'e' && arr[i + 4] == 'p')
    {
        i += 6;
        int you = strlen(arr);
        char *ijk = malloc(10);
        int yi = 0;
        for (int j = i; j < you; j++)
        {
            if (arr[j] == '\n')
                break;

            ijk[yi++] = arr[j];
        }
        ijk[yi++] = '\0';
        int pikachu = strtoint(ijk);
        if(pikachu>2)
        vals.tym=pikachu;
    }
    return vals;
}
