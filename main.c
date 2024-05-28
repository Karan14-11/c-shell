#include "terminal.h"
#include "directory.c"
#include "token.c"
#include "datastructures.c"
#include "complete.c"

int ctrlcno = 0;
int ctrlzno = 0;
int cook = 0;
int yuouo=0;
int ctrldno = 0;
char *current_process;
int ctrlzpid = -1;

void ctrlc(int sig_val)
{
    // signal(SIGINT, ctrlc);
    kill(ctrlznoo,SIGINT);
    ctrlznoo = 0;
    yuouo=1;
    return;
}
void ctrld(int sig_val)
{
    // signal(SIGQUIT, ctrld);
    ctrldno = 1;
    return;
}

void ctrlz(int q)
{

    // signal(SIGTSTP, ctrlz);
    // printf("%s HERE %d\n",globz,ctrlznoo);

    if (ctrlznoo == 0)
        return;
    else
    {

        // iv hk;
        // *gg=add_bg(*gg, ctrlznoo, globz);
        // llb* a;
        // for(a=gg->bglist;a!=NULL;a=a->nextnode)
        // printf("%s\n",a->name);
        cook = 1;
        kill(ctrlznoo, SIGSTOP);
        kill(ctrlznoo, SIGTSTP);
        return;
    }
}

int main()
{
    gg = malloc(sizeof(iv));
    signal(SIGINT, ctrlc);
    char *st_dir = finding_current_directory();
    iv vals;
    signal(SIGQUIT, ctrld);
    signal(SIGTSTP, ctrlz);
    vals.start_dir = malloc(MaxLimit);
    strcpy(vals.start_dir, st_dir);
    vals.last_dir = malloc(MaxLimit);
    strcpy(vals.last_dir, vals.start_dir);
    vals.pe = 0;
    vals.list = initialise_ll();
    vals.exit = 0;
    vals.tym = 0;
    vals.pipe = 0;
    vals.ampers=0;
    vals.bglist = NULL;
    char *tymstr = malloc(MaxLimit);
    clock_t start, end;
    globz=malloc(MaxLimit);
    double cpu_time_used;
    // gg= &vals;

    // signal(SIGTSTP, ctrlz);
    while (1)
    {
        if (cook == 1)
        {
            // printf("1\n");
            vals.list = add_node_ll(vals.list, ctrlznoo, globz);
            vals = add_bg(vals, ctrlznoo, globz);
            // cook = 0;
            ctrlznoo = 0;

        }
        start = clock();
        // vals.bglist=gg->bglist;
        vals.pe = 0;
        int c1 = starting_terminal();
        if (!c1)
            exit(1);
        char *sh_dir;
        sh_dir = finding_shell_directory(st_dir);
        char* act_dir;
        act_dir= finding_current_directory();
        if (vals.tym > 0 && ctrlcno == 0 && ctrlzno == 0&&vals.ampers==0&&yuouo==0&&cook==0)
        {
            int ikik = strlen(tymstr);
            for (int i = 0; i < ikik; i++)
            {
                if (tymstr[i] == '\n')
                    tymstr[i] == '\0';
            }
            printf("%s : %ds", tymstr, vals.tym);
        }
        cook=0;
        yuouo=0;
        ctrlcno = 0;
        if (sh_dir&&sh_dir[0] == '\0' )
            printf(">");
        else if (sh_dir)
        {
            printf("%s>", sh_dir);
        }
        else
        {
            printf("%s>",act_dir);
        }
        vals.tym = 0;
        vals.ampers=0;
        char input[4096];
        if (ctrlzno == 0)
        {
            char *uoi = fgets(input, 4096, stdin);
            if (uoi == NULL)
            {
                kill(getpid(), 9);
            }
        }
        else
        {
            strcpy(input, current_process);
            ctrlzno++;
        }
        current_process = input;

        int redirection;
        // if (ctrlzno == 0)
        if(vals.pe)
            vals = checking_comp(vals);

        vals = tokenise(input, vals);

        if (!vals.pe && ctrlzno == 0)
            vals = write_com(input, vals);

        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        if ((int)cpu_time_used > 2 && ctrlzno == 0 && vals.ampers==0)
        {
            strcpy(tymstr, input);
            vals.tym = cpu_time_used;
        }
        else if (vals.tym > 0 && ctrlzno == 0 )
        {
            strcpy(tymstr, "sleep");
        }

        if (vals.exit == 1 || ctrlzno == 2 ||ctrldno ==1)
        {
            break;
        }
    }
    return 0;
}