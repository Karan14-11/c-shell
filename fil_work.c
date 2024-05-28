#include "terminal.h"

int fil_work(char *path, char *rel_path, int y, int c, char *name)
{
    int ret = 0;

    struct dirent *current_directory;

    DIR *dir_ptr = opendir(path);
    int x = y;
    int d = c;
    if (dir_ptr == NULL)
        perror("");
    else
    {
        while ((current_directory = readdir(dir_ptr)) != NULL)
        {
            y = x;
            c = d;
            if (current_directory->d_type != DT_DIR)
            {
                if (current_directory->d_name[0] == '.')
                    continue;
                char *relc_path = malloc(MaxLimit);
                strcpy(relc_path, rel_path);
                relc_path[y++] = '/';
                char *copy_path = malloc(MaxLimit);
                strcpy(copy_path, path);
                copy_path[c++] = '/';

                int length = strlen(current_directory->d_name);

                for (int i = 0; i < length; i++)
                {
                    relc_path[y++] = current_directory->d_name[i];
                    copy_path[c++] = current_directory->d_name[i];
                }
                relc_path[y] = '\0';
                copy_path[c] = '\0';
                int i = 0;
                int ch = 1;
                char* io = malloc(MaxLimit);
                while (current_directory->d_name[i] != '\0' && current_directory->d_name[i] != '.')
                {

                    io[i]=current_directory->d_name[i] ;
                    // if (current_directory->d_name[i] != name[i])
                    // {

                    //     ch = 0;

                    //     break;
                    // }
                    i++;
                }
                io[i]='\0';
                if(strcmp(io,name)!=0)
                ch=0;
                if (ch)
                {
                    char *cat = malloc(MaxLimit);
                    cat[0] = 'c';
                    cat[1] = 'a';
                    cat[2] = 't';
                    cat[3] = ' ';
                    int cc = 4;
                    int lok = strlen(copy_path);
                    for (int kol = 0; kol < lok; kol++)
                    {
                        cat[cc++] = copy_path[kol];
                    }
                    cat[cc++] = '\0';

                    char *name[] = {
                        "/bin/bash",
                        "-c",
                        cat,
                        NULL};
                    if (fork() == 0)
                        execvp(name[0], name);
                    wait(NULL);
                    free(cat);
                }
            }
        }
    }
    closedir(dir_ptr);

    return ret;
}