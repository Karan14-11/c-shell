#include "terminal.h"

int dir_work(char *path, char *rel_path, int y, int c, char *name)
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
            if (current_directory->d_type == DT_DIR)
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

                int ch = 1;
                int i = 0;
                char *io = malloc(MaxLimit);
                while (current_directory->d_name[i] != '\0' && current_directory->d_name[i] != '.')
                {

                    io[i] = current_directory->d_name[i];
                    // if (current_directory->d_name[i] != name[i])
                    // {

                    //     ch = 0;

                    //     break;
                    // }
                    i++;
                }
                io[i]='\0';
                if (strcmp(io, name) != 0)
                    ch = 0;
                if (ch)
                {
                    chdir(copy_path);
                    ret+=1;
                }
                if (strcmp(rel_path, relc_path) != 0)
                    ret += dir_work(copy_path, relc_path, y, c, name);
                free(relc_path);
                free(copy_path);
            }
        }
    }
    closedir(dir_ptr);

    return ret;
}