#include "terminal.h"

llh *initialise_ll()
{
    llh *dummy = malloc(sizeof(llh));
    dummy->end = NULL;
    dummy->start = NULL;

    return dummy;
}

llh *add_node_ll(llh *head, int pid,char name[])
{
    if(head->start==NULL)
    {


        ll* temp= malloc(sizeof(ll));
        temp->nextnode=NULL;
        temp->pid=pid;
        temp->dummy=1;
        strcpy(temp->name,name);
        head->start= temp;
        head->end= temp;
        return head;
    }
    head->end->nextnode= malloc(sizeof(ll));
    head->end->nextnode->pid= pid;
    head->end->nextnode->dummy=1;
    strcpy(head->end->nextnode->name,name);
    head->end->nextnode->nextnode= NULL;
    head->end=head->end->nextnode;
    return head;
}

llh *delete_node_ll(llh* head)
{
    if(head->start==head->end)
    {
        ll* temp = head->end;
        head->end= NULL;
        head->start= NULL;
        free(temp);
        return head;
    }
    else
    {
        ll* temp= head->start;
        head->start=head->start->nextnode;
        free(temp);
        return head;
    }
}

void finish_list(llh* head)
{
    while(head->start!=NULL)
    {
        head=delete_node_ll(head);
    }
    free(head);
    return;
}

iv add_bg(iv vals,pid_t id, char* name)
{
    if(vals.bglist==NULL)
    {
       vals.bglist= malloc(sizeof(llb));
       vals.bglist->name=malloc(MaxLimit);
       strcpy(vals.bglist->name,name);
       vals.bglist->pid=id;
       vals.bglist->nextnode=NULL;
       return vals;        
    }
    llb* temp = vals.bglist;
    while(temp->nextnode&&temp->nextnode->pid>id)
    {
        temp=temp->nextnode;
    }
    llb* pocket = malloc(sizeof(llb));
    pocket->pid=id;
    pocket->name=malloc(MaxLimit);
    strcpy(pocket->name,name);
    pocket->nextnode=temp->nextnode;
    temp->nextnode=pocket;
    return vals;

}

iv* add_bg_ptr(iv* vals,pid_t id, char* name)
{
    if(vals->bglist==NULL)
    {
       vals->bglist= malloc(sizeof(llb));
       vals->bglist->name=malloc(MaxLimit);
       strcpy(vals->bglist->name,name);
       vals->bglist->pid=id;
       vals->bglist->nextnode=NULL;
       return vals;        
    }
    llb* temp = vals->bglist;
    while(temp->nextnode&&temp->nextnode->pid>id)
    {
        temp=temp->nextnode;
    }
    llb* pocket = malloc(sizeof(llb));
    pocket->pid=id;
    pocket->name=malloc(MaxLimit);
    strcpy(pocket->name,name);
    pocket->nextnode=temp->nextnode;
    temp->nextnode=pocket;
    return vals;

}