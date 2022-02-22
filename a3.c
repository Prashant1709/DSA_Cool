#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *next;
};
struct node *rear1 = NULL;
struct node *rear2 = NULL;
struct node *rear3 = NULL;
struct node *front1 = NULL;
struct node *front2 = NULL;
struct node *front3 = NULL;
void enque(int tkn_num, struct node **front, struct node **rear)
{
    struct node *newn = malloc(sizeof(struct node));
    newn->data = tkn_num;
    newn->next = NULL;
    if (*front == NULL)
    {
        *front = newn;
        *rear = newn;
        (*front)->next = NULL;
        (*rear)->next = NULL;
    }
    else
    {
        (*rear)->next = newn;
        *rear = newn;
        (*rear)->next = NULL;
    }
}
void display(struct node *q)
{
    struct node *ptr;
    ptr = q;
    while (ptr != NULL)
    {
        printf("\n%d\n", ptr->data);
        ptr = ptr->next;
    }
}
void create_queue(struct node **rear, struct node **front, int n)
{
    int i;
    static int tkn_num = 1;
    for (i = 0; i < n; i++)
    {
        struct node *newn = malloc(sizeof(struct node));
        newn->data = tkn_num;
        newn->next = NULL;

        if (*front == NULL)
        {
            *front = newn;
            *rear = newn;
            (*front)->next = NULL;
            (*rear)->next = NULL;
        }
        else
        {
            (*rear)->next = newn;
            *rear = newn;
            (*rear)->next = NULL;
        }
        tkn_num++;
    }
};
int deque(struct node **front)
{
    struct node *ptr;
    int num;
    num = (*front)->data;
    ptr = (*front);
    (*front) = (*front)->next;

    free(ptr);
    return num;
}
void go_vc()
{
    int tkn_num;

    while (front1 != NULL)
    {
        tkn_num = deque(&front1);

        printf("\n %d is in the vaccination centre", tkn_num);
        sleep(3);
        printf("\n %d is Vaccinated", tkn_num);
        if (front2 != NULL)
        {
            tkn_num = deque(&front2);
            printf("\n %d moving to queue 1", tkn_num);
            enque(tkn_num, &front1, &rear1);
            if (front3 != NULL)
            {
                tkn_num = deque(&front3);
                printf("\n %d moving to queue 2", tkn_num);
                enque(tkn_num, &front2, &rear2);
            }
        }
    }
    printf("\n Congratulations ! all people planned for today are vaccinated");
}
int main()
{
    int n, ppl_num, q;
    printf("enter the queue size\n");
    scanf("%d", &n);
    printf("enter total number of ppl present for vaccination\n");
    scanf("%d", &ppl_num);
    q = n * 3;
    printf("only the first %d ppl will get vaccinated\n", q);
    printf("rest can come tom \n");
    printf("here are your token number\n");
    create_queue(&rear1, &front1, n);
    display(front1);
    create_queue(&rear2, &front2, n);
    display(front2);
    create_queue(&rear3, &front3, n);
    display(front3);
    go_vc();
}