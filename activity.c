#include "terminal.h"

iv activity_fn(char *str, int start, iv vals)
{
    llb *temp = vals.bglist;
    // printf("&\n");
    while (temp != NULL)
    {
        // printf("6\n");
        char *path = malloc(MaxLimit);
        snprintf(path, MaxLimit, "/proc/%d/stat", temp->pid);
        FILE *a = fopen(path, "r");

        if (!a)
        {
            temp = temp->nextnode;
            continue;
        }
        char ch;
        int b = 0;
        char *op = malloc(MaxLimit);
        // printf("%s\n",op);
        fgets(op, MaxLimit, a);
        for (int i = 0; i < 3; i++)
        {
            int cnt = 0;
            while (op[b] != ' ')
            {
                path[cnt++] = op[b++];
            }
            b++;
            path[cnt++] = '\0';
        }
        if (path[0] != 'T' && path[0]!='Z')
        {
            int loni = strlen(temp->name);
            for(int j=0;j<loni;j++)
            {
                if(temp->name[j]=='\n')
                {
                    temp->name[j]='\0';
                    break;
                }
            }
            printf("%d ", temp->pid);
            printf(": %s - Running\n", temp->name);
        }
        else if(path[0]!='Z')
        {
            // printf("%s\n", path);
            int loni = strlen(temp->name);
            for(int j=0;j<loni;j++)
            {
                if(temp->name[j]=='\n')
                {
                    temp->name[j]='\0';
                    break;
                }
            }
            printf("%d ", temp->pid);
            printf(": %s - Stopped\n", temp->name);
        }
        free(path);
        temp = temp->nextnode;
        fclose(a);
    }
    return vals;
}