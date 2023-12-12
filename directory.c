#include "terminal.h"

#include "functions.h"


int starting_terminal()
{
    char *user_name = malloc(MaxLimit);
    int check_user = getlogin_r(user_name, MaxLimit);
    char *host_name = malloc(MaxLimit);
    int check_host = gethostname(host_name, MaxLimit);
    if (check_host && check_user == 0)
        return 0;

    printf("<%s@%s:~", user_name, host_name);
    return 1;
}

char *finding_shell_directory(char *h_dir)
{

    int hl = strlen(h_dir);
    char *c_dir = finding_current_directory();
    int cl = strlen(c_dir);
    for (int i = 0; i < hl; i++)
    {
        if (h_dir[i] != c_dir[i])
        {
            return NULL;
            
        }
    }
    char *r_dir = malloc(cl - hl + 10);
    int c = 0;
    for (int i = hl; i <= cl; i++)
    {
        r_dir[c++] = c_dir[i];
    }
    free(c_dir);
    return r_dir;
}

char *finding_current_directory()
{
    char directory[MaxLimit];
    getcwd(directory, sizeof(directory));
    char *return_val = malloc(100 + sizeof(directory));
    strcpy(return_val, directory);

    return return_val;
}

int calc_slashes(char *inp)
{
    int length = strlen(inp);
    int c = 0;
    for (int i = 0; i < length; i++)
    {
        if (inp[i] == '/')
            c++;
    }
    return c;
}

char *shelldirconv(char *h_dir,char*c_dir)
{

    int hl = strlen(h_dir);
    int cl = strlen(c_dir);
    for (int i = 0; i < hl; i++)
    {
        if (h_dir[i] != c_dir[i])
        {
            return NULL;
            
        }
    }
    char *r_dir = malloc(cl - hl + 10);
    int c = 0;
    r_dir[c++]='~';
    for (int i = hl; i <= cl; i++)
    {
        r_dir[c++] = c_dir[i];
    }
    return r_dir;
}