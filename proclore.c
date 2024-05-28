#include "terminal.h"

iv proclore_fn(char *str, int start, iv vals)
{
    start += 9;

    pid_t process_id;
    char *process_st;
    long long int virtual_memory;
    char *exec = malloc(MaxLimit);

    char *given_pid = malloc(MaxLimit);
    int lengthe = strlen(str);
    int oo = 0;
    for (int i = start; i < lengthe; i++)
    {
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
            break;
        given_pid[oo++] = str[i];
    }
    given_pid[oo++] = '\0';

    char *pid = malloc(MaxLimit);

    int length = strlen(str);
    int c = 0;
    for (int i = start; i < length; i++)
    {
        if (str[i] == '\n' || str[i] == '\t')
            break;
        pid[c++] = str[i];
    }
    pid[c++] = '\0';

    int cpid;
    if (pid[0] == '\0')
    {
        cpid = getpid();
    }
    else
        cpid = strtoint(given_pid);
    char *path = malloc(MaxLimit);
    char *stat = malloc(MaxLimit);
    char *status = malloc(MaxLimit);
    char *exe = malloc(MaxLimit);
    sprintf(stat, "/proc/%d/stat", cpid);
    sprintf(exe, "/proc/%d/exe", cpid);
    FILE *fptr = fopen(stat, "r");
    if (!fptr)
    {
        perror("");
    }
    else
    {
        char **temp_buf = malloc(sizeof(char *) * 100);
        for (int i = 0; i < 100; i++)
        {
            temp_buf[i] = malloc(MaxLimit);
        }
        char line[MaxLimit + 1];
        fgets(line, MaxLimit, fptr);
        int you = strlen(line);
        int index = 0;
        int cc = 0;
        for (int i = 0; i < you; i++)
        {
            if (line[i] == '\n' || line[i] == ' ')
            {
                temp_buf[index][c++] = '\0';
                c = 0;
                index++;
                continue;
            }
            temp_buf[index][c++] = line[i];
        }

        // char *token = strtok(fgets(line, 1000, fptr), " ");
        // temp_buf[0] = token;
        // token = strtok(NULL, " ");
        // int index = 1;
        // while (index < 24)
        // {
        //    temp_buf[index++] = token;
        // token = strtok(NULL, " ");
        //}

        process_st = temp_buf[2];
        int process_grp = strtoint(temp_buf[4]);
        int terminal_grp = strtoint(temp_buf[7]);
        virtual_memory = strtolong(temp_buf[22]);

        if (process_grp == terminal_grp)
        {
            process_st[1] = '+';
            process_st[2] = '\0';
        }
        else
        {
            process_st[1] = '\0';
        }
        printf("pid : %d\n", cpid);
        printf("process Status : %s\n", process_st);
        printf("process Group: %d\n", process_grp);
        printf("Memory : %lld\n", virtual_memory);
        fclose(fptr);
        for (int i = 0; i < 100; i++)
        {
            free(temp_buf[i]);
        }
        free(temp_buf);
    }
    ssize_t exe_ret;
    fptr = fopen(exe, "r");
    int a = 1;
    if (!fptr)
    {
        perror("");
        a = 0;
    }
    else
    {

        exe_ret = readlink(exe, exec, MaxLimit - 1);
        if (exe_ret == 1)
        {
            printf("READING ERROR\n");
            a = 0;
        }

        int plen = strlen(exec);
        int checko = 1;
        int hlen = strlen(vals.start_dir);
        if (plen > hlen)
        {
            for (int i = 0; i < hlen; i++)
            {

                if (exec[i] != vals.start_dir[i])
                {
                    checko = 0;
                    break;
                }
            }
            if (checko)
            {
                char *execu = shelldirconv(vals.start_dir, exec);
                printf("Executable path : %s\n", execu);
            }
        }
        if (plen < hlen || checko == 0)
            printf("Executable path : %s\n", exec);
    }

    if (a)
        fclose(fptr);

    return vals;
}
