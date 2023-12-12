#include "terminal.h"
#include "functions.h"

iv checking_comp(iv vals)
{
    int status, pidq;
    ll *temp = vals.list->start;
    if (temp == NULL)
    {
        return vals;
    }
    if ((pidq = waitpid(temp->pid, &status, WNOHANG)) == -1)
    {
        perror("wait() error");
        ll *a = temp;
        vals.list->start = temp->nextnode;
        free(a);
    }
    else if (pidq != 0)
    {
        if (WIFEXITED(status))
            printf("%s  exited with status of%d (%d)\n",temp->name, WEXITSTATUS(status), temp->pid);
        else
            printf("%s  exited  with error and status of%d (%d)\n",temp->name, WEXITSTATUS(status), temp->pid);
        // ll *a = temp;
        vals.list->start = temp->nextnode;
        // free(a);
    }
    // temp = vals.list->start;
    while (temp->nextnode != NULL)
    {

        if ((pidq = waitpid(temp->nextnode->pid, &status, WNOHANG)) == -1)
        {
            perror("wait() error");
        }
        else if (pidq != 0)
        {
            if (WIFEXITED(status))
            printf("%s  exited with status of %d (%d)\n",temp->name, WEXITSTATUS(status), temp->pid);
        else
            printf("%s  exited  with error and status of %d (%d)\n",temp->name, WEXITSTATUS(status), temp->pid);
            // ll *a = temp->nextnode;
            // free(a);
            // temp->nextnode = temp->nextnode->nextnode;
        }

        
    }
    return vals;
}