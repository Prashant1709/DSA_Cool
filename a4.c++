#include <iostream>
#include <climits>
using namespace std;

class queues
{
    int *arr;
    int *front;
    int *rear;
    int *next;
    int n, k;
    int free; 
public:
    queues(int k, int n);
    bool isFull() { return (free == -1); }
    void enqueue(int item, int qn);
    int dequeue(int qn);
    bool isEmpty(int qn) { return (front[qn] == -1); }
};

queues::queues(int k1, int n1)
{
    k = k1, n = n1;
    arr = new int[n];
    front = new int[k];
    rear = new int[k];
    next = new int[n];
    for (int i = 0; i < k; i++)
        front[i] = -1;

    free = 0;
    for (int i = 0; i < n - 1; i++)
        next[i] = i + 1;
    next[n - 1] = -1; // -1 is used to indicate end of free list
}

void queues::enqueue(int item, int qn)
{
    if (isFull())
    {
        cout << "\nQueue Overflow\n";
        return;
    }

    int i = free; // Store index of first free slot
    free = next[i];

    if (isEmpty(qn))
        front[qn] = i;
    else
        next[rear[qn]] = i;

    next[i] = -1;
    rear[qn] = i;
    arr[i] = item;
}
int queues::dequeue(int qn)
{
    if (isEmpty(qn))
    {
        cout << "\nQueue Underflow\n";
        return INT_MAX;
   }
    int i = front[qn];

    front[qn] = next[i]; // Change top to store next of previous top
    next[i] = free;
    free = i;
    return arr[i];
}
int main()
{
    int k = 4, n = 0,m=0,a=0,b=0,d=0,e=0;
    cout<<"Enter the size of the Array(even)\n";
    cin>>n;
    queues m1(k, n);
    do
    {
        cout<<"Enter your Option\n";
        cout<<"1. enqueue\n";
        cout << "2. dequeue\n";
        cout << "3. exit\n";
        cin>>m;
        switch(m)
        {
            case 1:
            
                do{
                cout<<"Enter the queue you want to enter in(1-4)\n";
                cin>>a;
                cout<<"Enter the value to enqueue\n";
                cin>>b;
                m1.enqueue(b,a);
                cout<<"Wanna enter more?\n";
                cin>>d;
                }while(d!=0);
            
            break;
            case 2:
            cout<<"Enter queue number to dequeue\n";
            cin>>e;
            cout<<"DeQueued element from queue "<<e<<" is "<<m1.dequeue(e)<<endl;
            break;
        }
    } while (m!=3);
    
    return 0;
}
