#include "terminal.h"

PF flag_check(char* str, int start)
{
    PF ret;
    ret.aflag=0;
    ret.lflag=0;
    
    if(str[start]!='-')
        return ret;
    else
    {
        start++;
        if(str[start]=='a' || str[start]=='l')
        {
            if(str[start]=='a')
            {
                ret.aflag=1;
                if(str[start+1]=='l'||(str[start+1]=='-'&&str[start+2]=='l'))
                    ret.lflag=1;
            }
            else if(str[start]=='l')
            {
                ret.lflag=1;
                if(str[start+1]=='a'||(str[start+1]=='l'&&str[start+2]=='l'))
                    ret.lflag=1;
            }
            return ret;

        }
        else
            return ret;
    }

}