#include "terminal.h"

iv checking_comp(iv vals)
{
    int status, pidq;
    int tp = 0;
    ll *temp = vals.list->start;
    while (temp != NULL)
    {
        if (temp->dummy == 0)
        {
            temp = temp->nextnode;
            continue;
        }
        pidq = waitpid(temp->pid, &status, WNOHANG);
        // if (pidq == 0)
        // {
        //     temp->dummy = 0;
        // }
        if (pidq > 0)
        {
            int ay;
            // printf("TYT%d\n", pidq);
            ay = WIFEXITED(status);
            printf("%s  exited with status of %d (%d)\n", temp->name, ay, temp->pid);
            temp->dummy=0;
        }
        temp=temp->nextnode;
    }
    
    return vals;
}