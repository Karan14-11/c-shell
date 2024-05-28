#ifndef _TERMINAL_
#define _TERMINAL_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ctype.h>
#include <termios.h>
#include <sys/stat.h>
#include<assert.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include"wait.h"
#include <signal.h>

#define MaxLimit 4095
#define input_rd 0
#define output_rd 1
#define append_rd 2
#define io_rd 3
#define ia_rd 4

typedef struct linkedlist_bg
{
    char* name;
    pid_t pid;
    struct linkedlist_bg* nextnode;
}llb;

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
    int dummy;
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
    int gl;
    llb* bglist;
    int pipe;
    int ampers;

}iv;

int ctrlznoo =0;
char* globz=NULL;
iv* gg=NULL;

iv seek_fn(char *str, int start, iv vals);
int starting_terminal();
int check_redirection(char* inp);
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
iv iman_fn(char* arr,int start,iv vals);
iv piping_fn(char*arr,iv vals);
lv check_lines(FILE* fptr);
char *readLine(FILE *file);
char notoas(int a);
llh *add_node_ll(llh *head, int pid,char name[]);
iv proclore_fn(char * str, int start, iv vals);
char *inttostr(int a, char *ret);
iv execute_fn(char* str, int start ,iv vals);
char *shelldirconv(char *h_dir,char*c_dir);
char *do_redirection(char *arr);
iv neonate_fn(char* arr,int start,iv vals);
iv add_bg(iv vals,pid_t id, char* name);
iv activity_fn(char *str, int start, iv vals);
iv ping_fn(char*arr,int start,iv vals);
iv fg_fn(char*str,int start,iv vals);
#endif
