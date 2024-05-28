#include "terminal.h"

lv check_lines(FILE *fptr)
{
    lv ret;
    ret.lines_written=0;
    ret.start_line=0;
    char *line = readLine(fptr);
    if (line[0] == '1')
        ret.lines_written += 10;
    int temp = (int)line[1];
    temp -= 48;
    ret.lines_written += temp;
    if(line[2]=='1')
        ret.start_line+=10;
    temp = (int)line[3];
    temp-=48;
    ret.start_line+=temp;
    
    return ret;

}
