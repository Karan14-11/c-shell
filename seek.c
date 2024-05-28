#include "terminal.h"
#include "seek_flag.c"
#include "dir_rec.c"
#include "fil_rec.c"
#include "fil_work.c"
#include "dir_work.c"

iv seek_fn(char *str, int start, iv vals)
{
    int countd = 0;
    int countf = 0;
    start += 5;
    SF check;
    struct stat info;

    check = flag_check_s(str, start);
    int sp = check.spaced;
    start += (sp);
    while (1)
    {
        if (str[start] != ' ' && str[start] != '\t')
            break;
        start++;
    }
    char *name = malloc(MaxLimit);
    int n = 0;
    while (str[start] != ' ')
    {
        if (str[start] == '\n' || str[start] == '\0')
            break;
        name[n++] = str[start++];
    }
    name[n] = '\0';
    // printf("%sHH\n",name);
    int length = strlen(str);
    char *dir_path = malloc(MaxLimit);
    char *rel_path = malloc(MaxLimit);
    int c = 0;
    int y = 0;
    int home_len = strlen(vals.start_dir);
    start++;
    if (str[start] == '~' || str[start] == '\n')
    {
        rel_path[y++] = '~';
        start++;
        for (int i = 0; i < home_len; i++)
            dir_path[c++] = vals.start_dir[i];
        for (int i = start; i <= length; i++)
        {
            if (str[i] == '\n' || str[i] == '\t')
                break;
            dir_path[c++] = str[i];
            rel_path[y++] = str[i];
        }
        dir_path[c] = '\0';
        rel_path[y] = '\0';
        if (check.dflag == 0 && check.fflag == 0)
        {
            countd += dir_rec(dir_path, rel_path, y, c, name);
            countf += fil_rec(dir_path, rel_path, y, c, name);
        }
        else if (check.dflag == 0)
        {
            countf += fil_rec(dir_path, rel_path, y, c, name);
        }
        else if (check.fflag == 0)
        {
            countd += dir_rec(dir_path, rel_path, y, c, name);
        }
    }
    else if ((str[start] == '.' && str[start + 1] != '.') || str[start] == '\0' || str[start - 1] == '\0')
    {
        start++;
        rel_path[y++] = '.';
        char *a = finding_current_directory();
        home_len = strlen(a);
        for (int i = 0; i < home_len; i++)
            dir_path[c++] = a[i];
        free(a);
        for (int i = start; i < length; i++)
        {
            if (str[i] == '\n' || str[i] == '\t')
                break;
            dir_path[c++] = str[i];
            rel_path[y++] = str[i];
        }

        dir_path[c] = '\0';
        rel_path[y] = '\0';
        if (check.dflag == 0 && check.fflag == 0)
        {
            countd += dir_rec(dir_path, rel_path, y, c, name);
            countf += fil_rec(dir_path, rel_path, y, c, name);
        }
        else if (check.dflag == 0)
        {
            countf += fil_rec(dir_path, rel_path, y, c, name);
        }
        else if (check.fflag == 0)
        {
            countd += dir_rec(dir_path, rel_path, y, c, name);
        }
    }
    else if (str[start] == '.' && str[start + 1] == '.')
    {
        start += 2;
        rel_path[y++] = '.';
        rel_path[y++] = '.';
        char *a = finding_current_directory();
        home_len = strlen(a);
        char *b = finding_shell_directory(vals.start_dir);
        // if (b[0] = '\0')
        // {
        //     perror("ALREADY IN HOME DIRECTORY__NO PARENT DIRECTORY\n");
        //     free(b);
        // }
        // else
        {
            free(b);
            int k = home_len;
            while (k != 0)
            {
                if (a[k--] == '/')
                    break;
            }
            for (int i = 0; i <= k; i++)
                dir_path[c++] = a[i];
            free(a);
            for (int i = start; i <= length; i++)
            {
                if (str[i] == '\n' || str[i] == '\t')
                    break;
                dir_path[c++] = str[i];
                rel_path[y++] = str[i];
            }
            dir_path[c] = '\0';
            if (check.dflag == 0 && check.fflag == 0)
            {
                countd += dir_rec(dir_path, rel_path, y, c, name);
                countf += fil_rec(dir_path, rel_path, y, c, name);

            }
            else if (check.dflag == 0)
            {
                countf += fil_rec(dir_path, rel_path, y, c, name);
            }
            else if (check.fflag == 0)
            {
                countd += dir_rec(dir_path, rel_path, y, c, name);
            }
        }
    }
    else if (str[start] == '-')
    {
        start++;
        rel_path[y++] = '-';
        home_len = strlen(vals.last_dir);
        for (int i = 0; i < home_len; i++)
            dir_path[c++] = vals.last_dir[i];

        for (int i = start; i <= length; i++)
        {
            if (str[i] == '\n' || str[i] == '\t')
                break;
            dir_path[c++] = str[i];
            rel_path[y++] = str[i];
        }
        dir_path[c] = '\0';

        if (check.dflag == 0 && check.fflag == 0)
        {
            countd += dir_rec(dir_path, rel_path, y, c, name);
            countf += fil_rec(dir_path, rel_path, y, c, name);
        }
        else if (check.dflag == 0)
        {
            countd += fil_rec(dir_path, rel_path, y, c, name);
        }
        else if (check.fflag == 0)
        {
            countf += dir_rec(dir_path, rel_path, y, c, name);
        }
    }
    if (countd == 0 && countf == 0)
        printf("NO MATCH FOUND!\n");
    if (check.dflag == 1 && check.fflag == 1)
        printf("INVALID FLAGS\n");
    if (countf == 1 && countd == 0 && check.eflag == 1)
    {
        fil_work(dir_path, rel_path, y, c, name);
    }
    if (countf == 0 && countd == 1 && check.eflag == 1)
    {
        dir_work(dir_path, rel_path, y, c, name);
    }

    free(dir_path);
    return vals;
}