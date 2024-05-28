#include "terminal.h"

iv warp_run(char *str, iv vals)
{
    int start = 0;
    int home_dir = 0;
    int par_dir = 0;
    int cur_dir = 0;
    int last_dir = 0;
    int homepath = 0;
    while (1)
    {
        if (str[start] == ' ')
        {
            start++;
            continue;
        }
        if (str[start] == '\t')
        {
            start++;
            continue;
        }
        if (str[start] == '\n')
        {
            start++;
            continue;
        }
        if (str[start] == '~'||str[start]=='\0')
        {
            home_dir = 1;
            if (str[start + 1] == '/')
                homepath = 1;
        }
        else if (str[start] == '.' && str[start + 1] == '.')
        {
            par_dir = 1;
        }
        else if (str[start] == '.')
        {
            cur_dir = 1;
        }
        else if (str[start] == '-')
        {
            last_dir = 1;
        }
        break;
    }
    if (last_dir == 1)
    {

        int a = chdir(vals.last_dir);
        if (a == -1)
            perror("");
        else
        {
            char *test = finding_current_directory();
            printf("%s\n", test);
            free(test);
        }
    }
    else
    {
        char *test = finding_current_directory();
        strcpy(vals.last_dir, test);
        free(test);

        if (home_dir == 1)
        {
            if (homepath == 1)
            {
                char* test2 = malloc(MaxLimit);
                int home_length=strlen(vals.start_dir);
                for(int j=0;j<home_length;j++)
                {
                    test2[j]=vals.start_dir[j];
                }
                int j=home_length;
                int pathlength= strlen(str);
                for(int k=1;k<pathlength;k++)
                {
                    if(str[k]=='\n'||str[k]=='\t')
                        break;
                    test2[j++]=str[k];
                }
                test2[j++]='/';
                test2[j++]='\0';
                int a = chdir(test2);
                if (a == -1)
                    perror("");
                else
                {
                    char *test = finding_current_directory();
                    printf("%s\n", test);
                    free(test);
                }
                free(test2);

            }
            else
            {
                int shdir = strlen(vals.start_dir);
                char *hdir = malloc(shdir + 10);
                strcpy(hdir, vals.start_dir);
                hdir[shdir] = '/';
                hdir[shdir + 1] = '\0';
                int a = chdir(hdir);
                if (a == -1)
                    perror("");
                else
                {
                    char *test = finding_current_directory();
                    printf("%s\n", test);
                    free(test);
                }
            }
        }
        else if (par_dir == 1)
        {
            char *test = finding_current_directory();
            char *test2 = finding_shell_directory(vals.start_dir);
            // if (test2[0] == '\0')
            // {
            //     free(test);
            //     free(test2);
            //     perror("Already in HOME DIRECTORY\n");
            // }
            // else
            {
                int len = strlen(test);
                int k = len;
                while (k >= 0)
                {
                    if (test[k--] != '/')
                        continue;
                    else
                    {
                        k++;
                        k++;
                        test[k] = '\0';
                        break;
                    }
                }
                int a = chdir(test);
                if (a == -1)
                {
                    printf("%s\n", test);
                    perror("");
                }
                else
                {
                    char *test3 = finding_current_directory();
                    printf("%s\n", test3);
                    free(test3);
                }
                free(test);
                free(test2);
            }
        }
        else if (cur_dir == 1)
        {
            char *test = finding_current_directory();
            printf("%s\n", test);
            free(test);
        }
        else
        {

            char *demopath = malloc(MaxLimit);

            int c = 1;
            int length = strlen(str);

            demopath[0] = '.';
            demopath[c++] = '/';
            for (int i = start; i < length; i++)
            {
                if (str[i] == '\n')
                    break;
                demopath[c++] = str[i];
            }
            demopath[c] = '/';
            demopath[++c] = '\0';
            int a = chdir(demopath);
            if (a == -1)
            {

                perror("");
            }
            else
            {
                char *test = finding_current_directory();
                printf("%s\n", test);
                free(test);
            }
        }
    }
    return vals;
}