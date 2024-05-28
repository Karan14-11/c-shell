#include "terminal.h"
#include "warp.c"
#include "peek.c"
#include "write_com.c"
#include "paste.c"
#include "backgrnd_fn.c"
#include "proclore.c"
#include "seek.c"
#include "purge.c"
#include "execute.c"
#include "redirection.c"
#include "pipe.c"
#include "activity.c"
#include "ping.c"
#include "fg.c"
#include "bg.c"
#include "neonate.c"
#include "iman.c"

iv default_terminal(char *arr, iv vals)
{
    int length = strlen(arr);
    int ampersand = 0;
    int piping = 0;
    for (int j = 0; j < length; j++)
    {
        if (arr[j] == '&')
        {
            ampersand = 1;
        }
        if (arr[j] == '|')
            piping = 1;
    }

    int def = 0;
    int i = 0;
    int bg = 0;
    int fg = 0;
    int warp = 0;
    int neonate = 0;
    int peek = 0;
    int iman = 0;
    int seek = 0;
    int pastevents = 0;
    int purge = 0;
    int proclore = 0;
    int activity = 0;
    int execute = 0;
    int ping = 0;
    int redirection = -1;
    // redirection = check_redirection(arr);
    iv rets;
    int oldin, oldout;
    if (vals.pipe == 0)
    {
        oldin = dup(0);
        oldout = dup(1);
        if (redirection != -1 && piping == 0)
        {
            arr = do_redirection(arr);
        }
    }

    while (arr[i] != '\0' && piping == 0)
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
        else if (arr[i] == 'i' && arr[i + 1] == 'M' && arr[i + 2] == 'a' && arr[i + 3] == 'n')
        {
            iman = 1;
            break;
        }
        else if (arr[i] == 'f' && arr[i + 1] == 'g')
        {
            fg = 1;
            break;
        }
        else if (arr[i] == 'b' && arr[i + 1] == 'g')
        {
            bg = 1;
            break;
        }
        else if (arr[i] == 'p' && arr[i + 1] == 'i' && arr[i + 2] == 'n' && arr[i + 3] == 'g')
        {
            ping = 1;
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
        else if (arr[i] == 'a' && arr[i + 1] == 'c' && arr[i + 2] == 't' && arr[i + 3] == 'i' && arr[i + 4] == 'v' && arr[i + 5] == 'i' && arr[i + 6] == 't' && arr[i + 7] == 'i' && arr[i + 8] == 'e' && arr[i + 9] == 's')
        {

            activity = 1;
            break;
        }
        else if (arr[i] == 'p' && arr[i + 1] == 'a' && arr[i + 2] == 's' && arr[i + 3] == 't' && arr[i + 4] == 'e' && arr[i + 5] == 'v' && arr[i + 6] == 'e' && arr[i + 7] == 'n' && arr[i + 8] == 't' && arr[i + 9] == 's' && arr[i + 10] == ' ' && arr[i + 11] == 'e' && arr[i + 12] == 'x' && arr[i + 13] == 'e' && arr[i + 14] == 'c' && arr[i + 15] == 'u' && arr[i + 16] == 't' && arr[i + 17] == 'e')
        {
            execute = 1;
            break;
        }
        else if (arr[i] == 'n' && arr[i + 1] == 'e' && arr[i + 2] == 'o' && arr[i + 3] == 'n' && arr[i + 4] == 'a' && arr[i + 5] == 't' && arr[i + 6] == 'e' && arr[i + 7] == ' ' && arr[i + 8] == '-' && arr[i + 9] == 'n')
        {
            neonate = 1;
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

    if (piping == 1)
    {
        vals = piping_fn(arr, vals);
    }
    else if (activity == 1)
    {
        vals = activity_fn(arr, i, vals);
    }
    else if (warp == 1 && ampersand == 0)
    {
        vals = warp_fn(arr, i, vals);
    }
    else if (iman == 1 && ampersand == 0)
    {
        vals = iman_fn(arr, i, vals);
    }
    else if (neonate == 1 && ampersand == 0)
    {
        vals = neonate_fn(arr, i, vals);
    }
    else if (ping == 1)
    {
        vals = ping_fn(arr, i, vals);
    }
    else if (peek == 1 && ampersand == 0)
    {
        vals = peek_fn(arr, i, vals);
    }
    else if (fg == 1 && ampersand == 0)
    {
        vals = fg_fn(arr, i, vals);
    }
    else if (bg == 1 && ampersand == 0)
    {
        vals = bg_fn(arr, i, vals);
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
        vals.pe = 2;
    }
    else
    {
        if (ampersand == 0)
        {

            if (vals.pipe == 0)
            {
                int oldin1 = dup(0);
                int oldout1 = dup(1);
            }
            char *name[] = {
                "/bin/bash",
                "-c",
                arr,
                NULL};
            int you = fork();
            // ctrlznoo = you;
            strcpy(globz,arr);
            if (you == 0)
            {
                setpgid(0,0);
                execvp(name[0], name);
            }
            ctrlznoo = you;
            int status;
            waitpid(you,&status,WUNTRACED);
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
        if (pikachu > 2)
            vals.tym = pikachu;
    }
    if (vals.pipe)
    {
        fflush(stdout);
        dup2(oldin, 0);
        dup2(oldout, 1);
    }

    return vals;
}
