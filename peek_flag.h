#ifndef _PEAKFLAG_
#define _PEAKFLAG_

typedef struct peek_flag
{
    int lflag;
    int aflag;
}PF;

PF flag_check(char* str, int start);

#endif
