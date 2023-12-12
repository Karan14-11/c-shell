#include "terminal.h"
#include "functions.h"

SF flag_check_s(char *str, int start)
{
    SF ret;
    ret.dflag = 0;
    ret.eflag = 0;
    ret.fflag = 0;
    ret.spaced=0;
   
    while(1)
    {
        if(str[start]==' '||str[start]=='\t'||str[start]=='\n')
        {
            ret.spaced++;
            start++;
            continue;
        }
        if(str[start]=='-')
        {
            ret.spaced++;
            start++;
            if(str[start]=='d')
            ret.dflag=1;
            if(str[start]=='e')
            ret.eflag=1;
            if(str[start]=='f')
            ret.fflag=1;
            start++;
            continue;            
        }
        break;
    }
    return ret;
}