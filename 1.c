#include <stdio.h>
#include <stdlib.h>
struct node
{
    int pid;
    int CPU_time;
    struct node *next;
    struct node *prev;
} *start = NULL, *last = NULL;
int CPU_Time;
int count = 0 ;
const int T;
void creat_list(struct node **st, struct node **lt, int pid,int CPU_Time);
void trf();
void exec() ;
void MTE(struct node **head) ;
void delf();
int main()
{
    int pid,choice,s;
    char c;
    printf("Enter the number of processes\n");
    scanf("%d",&count);
    for (int i = 0; i < count; i++)
    {
        printf("Enter the PID\n");
        scanf("%d",&pid);
        printf("Enter the CPU Time\n");
        scanf("%d", &CPU_Time);
        creat_list(&start,&last,pid,CPU_Time);
    }
    printf("Enter the Quanta Time\n");
    scanf("%d",&T);
    trf();
    exec();
    
}
void creat_list(struct node **st, struct node **lt, int pid,int CPU_Time)
{
    int n1 = pid;
    int n2 = CPU_Time;
    struct node *new = (struct node *)malloc(sizeof(struct node *));
    new->pid = n1;
    new->CPU_time=n2;
    new->next = NULL;
    new->prev = NULL;
    if ((*st) == NULL)
    {
        *st = new;
        *lt = new;
    }
    else
    {
        new->prev = last;
        (*lt)->next = new;
        (*lt) = new;
    }
}
void trf()
{
    struct node *t1;
    t1 = start;
    while (t1 != NULL)
    {
        printf("PID %d->", t1->pid);
        printf("CPU_Time %d\n",t1->CPU_time);
        t1 = t1->next;
    }
}
void exec()
{
    
    struct node *temp;
    temp=start;
    while(start!=NULL)
    {
        if (temp->CPU_time<=0)
        {
            printf("\nProcess PID %d execution completed.....process deleted from queue", temp->pid);
            delf();
            count--;  
        }
        else
        {
            
            temp->CPU_time=temp->CPU_time-T;//7-4 and store 3
            if (temp->CPU_time==0)
            {
                printf("Process PID %d execution completed.....process deleted from queue", temp->pid);
                delf();
                count--;
            }
            else{
                    printf("The PID %d was executed for %d time and is shifted to end with remaing time %d\n",temp->pid,T,temp->CPU_time);
                    MTE(&temp);
            }
        }
    }    
        
    
    
    

}
void delf()
{
    struct node *t;
    t = start;
    if (t == NULL)
    {
        printf("Cant delete\n");
    }
    else
    {
        t = start;
        start = start->next;
        start->prev = NULL;
        free(t);
    }
}
void MTE(struct node **head)
{
     if (*head == NULL || (*head)->next == NULL)
        return;

    struct node *first = *head;
    struct node *last = *head;

    while (last->next != NULL)
    {
        last = last->next;
    }

    *head = first->next;

    first->next = NULL;

    last->next = first;
}