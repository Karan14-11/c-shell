
#ifndef _FX_
#define _FX_
#define MaxLimit 4095


typedef struct peek_flag
{
    int lflag;
    int aflag;
}PF;

typedef struct seek_flag
{
    int dflag;
    int eflag;
    int fflag;
    int spaced;
}SF;

typedef struct lines_val
{
    int lines_written;
    int start_line;
}lv;


typedef struct linkedlist
{
    int pid;
    char name[MaxLimit];
    struct linkedlist * nextnode;
}ll;

typedef struct llhead
{
    ll* start;
    ll* end;
}llh;

typedef struct imp_vals
{
    char *start_dir;
    char *last_dir;
    int  pe;
    llh* list;
    int exit;
    int tym;

}iv;

iv seek_fn(char *str, int start, iv vals);
int starting_terminal();
char *finding_current_directory();
char *finding_shell_directory(char *h_dir);
iv default_terminal(char *arr, iv vals);
int calc_slashes(char *inp);
iv backgrnd_fn(char*arr,int start,iv vals);
iv warp_fn(char *str, int start, iv vals);
iv tokenise(char *str, iv vals);
PF flag_check(char* str, int start);
iv write_com(char* inp, iv vals);
iv paste_fn(char* str,int start, iv vals);
iv write_com(char* inp, iv vals);
lv check_lines(FILE* fptr);
char *readLine(FILE *file);
char notoas(int a);
llh *add_node_ll(llh *head, int pid,char name[]);
iv proclore_fn(char * str, int start, iv vals);
char *inttostr(int a, char *ret);
iv execute_fn(char* str, int start ,iv vals);
char *shelldirconv(char *h_dir,char*c_dir);
llh *initialise_ll();
iv checking_comp(iv vals);


//peek
iv peek_fn(char *str, int start, iv vals);

//purge 
iv purge_fn(char* str,int start,iv vals);

// no ascee
int strtoint(char *a);
long long int strtolong(char *a);

// seek & seek derivatives
SF flag_check_s(char *str, int start);
int dir_rec(char *path, char *rel_path, int y, int c, char *name);
int fil_rec(char *path, char *rel_path, int y, int c, char *name);
int dir_work(char *path, char *rel_path, int y, int c, char *name);
int fil_work(char *path, char *rel_path, int y, int c, char *name);


//warp
iv warp_run(char *str, iv vals);
iv warp_tok(char *str, iv vals);


#endif