#include "terminal.h"
#include "functions.h"

int main()
{
    char *st_dir = finding_current_directory();
    iv vals;
    vals.start_dir = malloc(MaxLimit);
    strcpy(vals.start_dir, st_dir);
    vals.last_dir = malloc(MaxLimit);
    strcpy(vals.last_dir, vals.start_dir);
    vals.pe = 0;
    vals.list = initialise_ll();
    vals.exit = 0;
    vals.tym=0;
    char* tymstr = malloc(MaxLimit);

    // FILE* fno;
    // char *type = malloc(10);
    // type[0] = '0';
    // type[1] = '0';
    // type[2] = '0';
    // type[3] = '0';
    // type[4] = '\0';
    // fno = fopen("nos.txt", "w");
    // fwrite(type, 1, strlen(type), fno);
    // fclose(fno);

    clock_t start, end;
    double cpu_time_used;

    while (1)
    {
        start = clock();
        vals.pe = 0;
        int c1 = starting_terminal();
        if (!c1)
            exit(1);
        char *sh_dir = finding_shell_directory(st_dir);
        if(vals.tym>0)
        {
            printf("%s : %ds",tymstr,vals.tym);
        }
        if (sh_dir[0] == '\0')
            printf(">");
        else
        {
            printf("%s>", sh_dir);
        }
        vals.tym=0;
        char input[4096];
        fgets(input, 4096, stdin);

        if (vals.pe==1)
            vals = checking_comp(vals);
        vals = tokenise(input, vals);
        if (!vals.pe)
            vals = write_com(input, vals);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        if((int)cpu_time_used>2)
        {
            strcpy(tymstr,input);
            vals.tym=cpu_time_used;
        }
        else if(vals.tym>0)
        {
           strcpy(tymstr,"sleep"); 
        }
        if(vals.exit==1)
        break;

    }
    return 0;
}