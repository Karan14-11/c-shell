#include "terminal.h"

int check_redirection(char *input)
{
    int length = strlen(input);
    int inp = 0;
    int out = 0;
    int app = 0;
    for (int i = 0; i < length; i++)
    {
        if (input[i] == '<')
            inp = 1;
        if (input[i] == '>')
        {
            if (input[i + 1] == '>')
                app = 1;
            out = 1;
        }
    }
    if (inp == 1)
    {
        return 1;
    }
    else if (app == 1)
        return 1;
    else if (out == 1)
        return 1;
    return -1;
}

char *do_redirection(char *arr)
{
    int i = 0;
    int ret = 0;
    while (1)
    {
        if (arr[i] == '\0')
            break;
        if (arr[i] == '\n')
            break;
        if (arr[i] == '<')
        {
            ret = i;
            i++;
            char *input_path = malloc(MaxLimit);
            while (arr[i] == '\t' || arr[i] == ' ')
                i++;
            int c = 0;
            input_path[c++] = '.';
            input_path[c++] = '/';
            while (arr[i] != ' ')
            {
                if(arr[i]=='\n' || arr[i]=='\t'||arr[i]=='\0')
                    break;
                input_path[c++] = arr[i++];
            }
            input_path[c] = '\0';

            FILE *fptr;
            fptr = freopen(input_path, "r", stdin);
            if (!fptr)
                perror("Invalid File Path !");
            free(input_path);
        }
        if (arr[i] == '>' && arr[i + 1] == '>')
        {
            ret = i;
            i++;
            i++;
            char *input_path = malloc(MaxLimit);
            while (arr[i] == '\t' || arr[i] == ' ')
                i++;
            int c = 0;
            input_path[c++] = '.';
            input_path[c++] = '/';
            while (arr[i] != ' ')
            {
                if(arr[i]=='\n' || arr[i]=='\t'||arr[i]=='\0')
                    break;
                input_path[c++] = arr[i++];
            }
            input_path[c] = '\0';
            FILE *fptr;
            fptr = freopen(input_path, "a", stdout);
            if (!fptr)
                perror("Invalid File Path !");
            free(input_path);
        }
        if (arr[i] == '>')
        {
            ret = i;
            i++;
            char *input_path = malloc(MaxLimit);
            while (arr[i] == '\t' || arr[i] == ' ')
                i++;
            int c = 0;
            input_path[c++] = '.';
            input_path[c++] = '/';
            while (arr[i] != ' ')
            {
                if(arr[i]=='\n' || arr[i]=='\t'||arr[i]=='\0')
                    break;
                input_path[c++] = arr[i++];
            }
            input_path[c] = '\0';
            FILE *fptr;
            fptr = freopen(input_path, "w", stdout);
            if (!fptr)
                perror("Invalid File Path !");
            free(input_path);
        }
        i++;
    }
    arr[ret] = '\0';
    return arr;
}