#include "terminal.h"
#include "peek_flag.c"

int directoryqsort(const struct dirent **a, const struct dirent **b)
{
    return strcmp((*a)->d_name, (*b)->d_name);
}

iv peek_fn(char *str, int start, iv vals)
{

    start += 5;
    PF check;
    struct stat info;

    check = flag_check(str, start);
    if (str[start] == '-' && (str[start + 1] == 'a' || str[start + 1] == 'l'))
    {
        start += 2;
        if (str[start] == 'a' || str[start] == 'l')
            start++;
    }
    if (str[start] == '-' && (str[start + 1] == 'a' || str[start + 1] == 'l'))
    {
        start += 2;
        if (str[start] == 'a' || str[start] == 'l')
            start++;
    }
    while (1)
    {
        if (str[start] != ' ' && str[start] != '\n' && str[start] != '\t')
            break;
        start++;
    }
    int length = strlen(str);
    char *dir_path = malloc(MaxLimit);
    int c = 0;
    int home_len = strlen(vals.start_dir);
    if (str[start] == '~' )
    {
        start++;
        for (int i = 0; i < home_len; i++)
            dir_path[c++] = vals.start_dir[i];
        for (int i = start; i < length; i++)
        {
            if (str[i] == '\n' || str[i] == '\t')
                break;
            dir_path[c++] = str[i];
        }
        dir_path[c] = '\0';

        // DIR *dir_ptr = opendir(dir_path);

        // if (dir_ptr == NULL)
        //     perror("");
        // else

        struct dirent **current_directory;

        int total = scandir(dir_path, &current_directory, NULL, directoryqsort);
        for (int i = 0; i < total; i++)
        {
            if (check.aflag == 0 && check.lflag == 0)
            {
                stat(current_directory[i]->d_name, &info);

                if (current_directory[i]->d_name[0] == '.')
                    continue;
                if (current_directory[i]->d_type == DT_DIR)
                    printf(" \033[1;34m %s\n\033[0m", current_directory[i]->d_name);
                else if (info.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
                    printf(" \033[1;32m %s\n\033[0m", current_directory[i]->d_name);
                else
                    printf(" \033[1;37m %s\n\033[0m", current_directory[i]->d_name);
            }
            else if (check.aflag == 1 && check.lflag == 0)
            {
                stat(current_directory[i]->d_name, &info);

                if (current_directory[i]->d_type == DT_DIR)
                    printf(" \033[1;34m %s\n\033[0m", current_directory[i]->d_name);
                else if (info.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
                    printf(" \033[1;32m %s\n\033[0m", current_directory[i]->d_name);
                else
                    printf(" \033[1;37m %s\n\033[0m", current_directory[i]->d_name);
            }
            if (check.lflag == 1)
            {
                if (current_directory[i]->d_name[0] == '.' && check.aflag == 0)
                    continue;
                stat(current_directory[i]->d_name, &info);
                printf("d");
                (info.st_mode & S_IRUSR) ? printf("r") : printf("-");
                (info.st_mode & S_IWUSR) ? printf("w") : printf("-");
                (info.st_mode & S_IXUSR) ? printf("x") : printf("-");
                (info.st_mode & S_IRGRP) ? printf("r") : printf("-");
                (info.st_mode & S_IWGRP) ? printf("w") : printf("-");
                (info.st_mode & S_IXGRP) ? printf("x") : printf("-");
                (info.st_mode & S_IROTH) ? printf("r") : printf("-");
                (info.st_mode & S_IWOTH) ? printf("w") : printf("-");
                (info.st_mode & S_IXOTH) ? printf("x") : printf("-");
                printf(" %ld", info.st_nlink);
                struct passwd *pw = getpwuid(info.st_uid);
                struct group *gr = getgrgid(info.st_gid);
                if (pw)
                    printf(" %s", pw->pw_name);
                if (gr)
                    printf(" %s", gr->gr_name);
                printf(" %ld", info.st_size);
                char t[100] = "";
                strftime(t, 100, "%b %d %H:%M", localtime(&info.st_mtime));
                printf(" %s", t);

                if (current_directory[i]->d_type == DT_DIR)
                    printf(" \033[1;34m %s\n\033[0m", current_directory[i]->d_name);
                else if (info.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
                    printf(" \033[1;32m %s\n\033[0m", current_directory[i]->d_name);
                else
                    printf(" \033[1;37m %s\n\033[0m", current_directory[i]->d_name);
            }
        }
    }

    else if (str[start] == '.' && str[start + 1] != '.'|| str[start]=='\0' || str[start]=='\n')
    {
        start++;
        char *a = finding_current_directory();
        home_len = strlen(a);
        for (int i = 0; i < home_len; i++)
            dir_path[c++] = a[i];
        free(a);
        for (int i = start; i <= length; i++)
        {
            if (str[i] == '\n' || str[i] == '\t')
                break;
            dir_path[c++] = str[i];
        }
        dir_path[c] = '\0';

        struct dirent **current_directory;

        int total = scandir(dir_path, &current_directory, NULL, directoryqsort);
        for (int i = 0; i < total; i++)
        {
            if (check.aflag == 0 && check.lflag == 0)
            {
                stat(current_directory[i]->d_name, &info);

                if (current_directory[i]->d_name[0] == '.')
                    continue;
                if (current_directory[i]->d_type == DT_DIR)
                    printf(" \033[1;34m %s\n\033[0m", current_directory[i]->d_name);
                else if (info.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
                    printf(" \033[1;32m %s\n\033[0m", current_directory[i]->d_name);
                else
                    printf(" \033[1;37m %s\n\033[0m", current_directory[i]->d_name);
            }
            else if (check.aflag == 1 && check.lflag == 0)
            {
                stat(current_directory[i]->d_name, &info);

                if (current_directory[i]->d_type == DT_DIR)
                    printf(" \033[1;34m %s\n\033[0m", current_directory[i]->d_name);
                else if (info.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
                    printf(" \033[1;32m %s\n\033[0m", current_directory[i]->d_name);
                else
                    printf(" \033[1;37m %s\n\033[0m", current_directory[i]->d_name);
            }
            if (check.lflag == 1)
            {
                if (check.aflag == 0 && current_directory[i]->d_name[0] == '.')
                    continue;
                stat(current_directory[i]->d_name, &info);
                printf("d");
                (info.st_mode & S_IRUSR) ? printf("r") : printf("-");
                (info.st_mode & S_IWUSR) ? printf("w") : printf("-");
                (info.st_mode & S_IXUSR) ? printf("x") : printf("-");
                (info.st_mode & S_IRGRP) ? printf("r") : printf("-");
                (info.st_mode & S_IWGRP) ? printf("w") : printf("-");
                (info.st_mode & S_IXGRP) ? printf("x") : printf("-");
                (info.st_mode & S_IROTH) ? printf("r") : printf("-");
                (info.st_mode & S_IWOTH) ? printf("w") : printf("-");
                (info.st_mode & S_IXOTH) ? printf("x") : printf("-");
                printf(" %ld", info.st_nlink);
                struct passwd *pw = getpwuid(info.st_uid);
                struct group *gr = getgrgid(info.st_gid);
                if (pw)
                    printf(" %s", pw->pw_name);
                if (gr)
                    printf(" %s", gr->gr_name);
                printf(" %ld", info.st_size);
                char t[100] = "";
                strftime(t, 100, "%b %d %H:%M", localtime(&info.st_mtime));
                printf(" %s", t);

                if (current_directory[i]->d_type == DT_DIR)
                    printf(" \033[1;34m %s\n\033[0m", current_directory[i]->d_name);
                else if (info.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
                    printf(" \033[1;32m %s\n\033[0m", current_directory[i]->d_name);
                else
                    printf(" \033[1;37m %s\n\033[0m", current_directory[i]->d_name);
            }
        }
    }
    else if (str[start] == '.' && str[start + 1] == '.')
    {
        start += 2;
        char *a = finding_current_directory();
        home_len = strlen(a);
        char *b = finding_shell_directory(vals.start_dir);
        if (b[0] = '\0')
        {
            perror("ALREADY IN HOME DIRECTORY__NO PARENT DIRECTORY\n");
            free(b);
        }
        else
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
            }
            dir_path[c] = '\0';

            struct dirent **current_directory;

            int total = scandir(dir_path, &current_directory, NULL, directoryqsort);
            for (int i = 0; i < total; i++)
            {
                if (check.aflag == 0 && check.lflag == 0)
                {
                    stat(current_directory[i]->d_name, &info);

                    if (current_directory[i]->d_name[0] == '.')
                        continue;
                    if (current_directory[i]->d_type == DT_DIR)
                        printf(" \033[1;34m %s\n\033[0m", current_directory[i]->d_name);
                    else if (info.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
                        printf(" \033[1;32m %s\n\033[0m", current_directory[i]->d_name);
                    else
                        printf(" \033[1;37m %s\n\033[0m", current_directory[i]->d_name);
                }
                else if (check.aflag == 1 && check.lflag == 0)
                {
                    stat(current_directory[i]->d_name, &info);

                    if (current_directory[i]->d_type == DT_DIR)
                        printf(" \033[1;34m %s\n\033[0m", current_directory[i]->d_name);
                    else if (info.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
                        printf(" \033[1;32m %s\n\033[0m", current_directory[i]->d_name);
                    else
                        printf(" \033[1;37m %s\n\033[0m", current_directory[i]->d_name);
                }
                if (check.lflag == 1)
                {
                    if (check.aflag == 0 && current_directory[i]->d_name[0] == '.')
                        continue;
                    stat(current_directory[i]->d_name, &info);
                    printf("d");
                    (info.st_mode & S_IRUSR) ? printf("r") : printf("-");
                    (info.st_mode & S_IWUSR) ? printf("w") : printf("-");
                    (info.st_mode & S_IXUSR) ? printf("x") : printf("-");
                    (info.st_mode & S_IRGRP) ? printf("r") : printf("-");
                    (info.st_mode & S_IWGRP) ? printf("w") : printf("-");
                    (info.st_mode & S_IXGRP) ? printf("x") : printf("-");
                    (info.st_mode & S_IROTH) ? printf("r") : printf("-");
                    (info.st_mode & S_IWOTH) ? printf("w") : printf("-");
                    (info.st_mode & S_IXOTH) ? printf("x") : printf("-");
                    printf(" %ld", info.st_nlink);
                    struct passwd *pw = getpwuid(info.st_uid);
                    struct group *gr = getgrgid(info.st_gid);
                    if (pw)
                        printf(" %s", pw->pw_name);
                    if (gr)
                        printf(" %s", gr->gr_name);
                    printf(" %ld", info.st_size);
                    char t[100] = "";
                    strftime(t, 100, "%b %d %H:%M", localtime(&info.st_mtime));
                    printf(" %s", t);

                    if (current_directory[i]->d_type == DT_DIR)
                        printf(" \033[1;34m %s\n\033[0m", current_directory[i]->d_name);
                    else if (info.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
                        printf(" \033[1;32m %s\n\033[0m", current_directory[i]->d_name);
                    else
                        printf(" \033[1;37m %s\n\033[0m", current_directory[i]->d_name);
                }
            }
        }
    }
    else if (str[start] == '-')
    {
        start++;
        home_len = strlen(vals.last_dir);
        for (int i = 0; i < home_len; i++)
            dir_path[c++] = vals.last_dir[i];

        for (int i = start; i <= length; i++)
        {
            if (str[i] == '\n' || str[i] == '\t')
                break;
            dir_path[c++] = str[i];
        }
        dir_path[c] = '\0';

        struct dirent **current_directory;

        int total = scandir(dir_path, &current_directory, NULL, directoryqsort);
        for (int i = 0; i < total; i++)
        {
            if (check.aflag == 0 && check.lflag == 0)
            {
                stat(current_directory[i]->d_name, &info);

                if (current_directory[i]->d_name[0] == '.')
                    continue;
                if (current_directory[i]->d_type == DT_DIR)
                    printf(" \033[1;34m %s\n\033[0m", current_directory[i]->d_name);
                else if (info.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
                    printf(" \033[1;32m %s\n\033[0m", current_directory[i]->d_name);
                else
                    printf(" \033[1;37m %s\n\033[0m", current_directory[i]->d_name);
            }
            else if (check.aflag == 1 && check.lflag == 0)
            {
                stat(current_directory[i]->d_name, &info);

                if (current_directory[i]->d_type == DT_DIR)
                    printf(" \033[1;34m %s\n\033[0m", current_directory[i]->d_name);
                else if (info.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
                    printf(" \033[1;32m %s\n\033[0m", current_directory[i]->d_name);
                else
                    printf(" \033[1;37m %s\n\033[0m", current_directory[i]->d_name);
            }
            if (check.lflag == 1)
            {

                if (check.aflag == 0 && current_directory[i]->d_name[0] == '.')
                    continue;
                stat(current_directory[i]->d_name, &info);
                printf("d");
                (info.st_mode & S_IRUSR) ? printf("r") : printf("-");
                (info.st_mode & S_IWUSR) ? printf("w") : printf("-");
                (info.st_mode & S_IXUSR) ? printf("x") : printf("-");
                (info.st_mode & S_IRGRP) ? printf("r") : printf("-");
                (info.st_mode & S_IWGRP) ? printf("w") : printf("-");
                (info.st_mode & S_IXGRP) ? printf("x") : printf("-");
                (info.st_mode & S_IROTH) ? printf("r") : printf("-");
                (info.st_mode & S_IWOTH) ? printf("w") : printf("-");
                (info.st_mode & S_IXOTH) ? printf("x") : printf("-");
                printf(" %ld", info.st_nlink);
                struct passwd *pw = getpwuid(info.st_uid);
                struct group *gr = getgrgid(info.st_gid);
                if (pw)
                    printf(" %s", pw->pw_name);
                if (gr)
                    printf(" %s", gr->gr_name);
                printf(" %ld", info.st_size);
                char t[100] = "";
                strftime(t, 100, "%b %d %H:%M", localtime(&info.st_mtime));
                printf(" %s", t);

                if (current_directory[i]->d_type == DT_DIR)
                    printf(" \033[1;34m %s\n\033[0m", current_directory[i]->d_name);
                else if (info.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
                    printf(" \033[1;32m %s\n\033[0m", current_directory[i]->d_name);
                else
                    printf(" \033[1;37m %s\n\033[0m", current_directory[i]->d_name);
            }
        }
    }
    free(dir_path);
    return vals;
}