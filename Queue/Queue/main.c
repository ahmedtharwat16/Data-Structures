#include <stdio.h>
#include <stdlib.h>
#include<string.h>

/*
 * Process: Each process has a name and has an execution time.
 *          We keep track of how long the process still needs
 *          to run on the processor. "remaining_time" is the
 *          remaining execution time of the process.
 * Item: An item that is being enqueued to or dequeued from the queue
 *       It is a pointer to the process
 */
typedef struct
{
    char *name[10];
    int remaining_time;
    int bt;
}Process , *Item;
/*
 *
 */
typedef struct Node
{
    Item data;
    struct Node* next;
} Node;
/*
 *
 */

typedef struct
{
    int front,back,numberofitems;
    int Capacity;
    int *items;
    
} Queue;
/*
 *
 */
void init(Queue *q)
{
    q->front=q->back=NULL;
    q->Capacity=10;
    q->numberofitems=0;
    q->items=(Queue*)malloc(10*sizeof(Queue));
}
/*
 *
 */
int isEmpty(Queue *q)
{
    if(q->numberofitems==NULL)
        return 1;
    else
        return 0 ;
}
/*
 *
 */
Item dequeue(Queue *q)
{
    int data=q->items[q->front];
    q->front=(q->front+1)%q->Capacity;
    q->numberofitems--;
    return data;
    
}
/*
 *
 */
void enqueue(Queue *q, Item val)
{
    q->items[q->back]=val;
    q->back=(q->back+1)%q->Capacity;
    q->numberofitems++;
}
/*
 *
 */
Item destroy(Queue *q)
{
    int data;
    while(q->items[q->front])
        data=q->items[q->front];
    dequeue(&q);
    return data;
}
/*
 * RoundRobin Scheduling
 */

//FUNCTION TO READ FILE
int readfile(FILE *f, Process p []   )
{ int i=0;
    
    f=fopen("abc.txt","r");
    while(!feof(f))
    {
        fscanf(f,"%s %d %d",p[i].name,&p[i].bt, &p[i].remaining_time);
        // printf("%s %d---%d\n",p[i].name,p[i].bt,p[i].remaining_time);
        i++;
    }
    
    fclose(f);
    return i; //number of processes
}

//FUNCTION TO CHECK THE BIRTHTIME
void checkbirthtime(Process p[], Queue *q,int x)
{  FILE*f;
    int i=0;
    //int  numberofp = readfile(f,p);
    for(i=0 ; i < 4/*numberofp*/ ; i++ )
    {        if(p[i].bt == x)
        enqueue(q,&p[i]);
        
    }
    
    
}
void checkquantum(Item k, Queue * q)
{
    if(k->remaining_time == 0)
        //if time of processor is finished the process aborts
        printf("%s aborts",k->name);
    else
        //if not it is resent to the end of the queue
        enqueue(q,k);
}

void RoundRobin(char* filename)
{int i;
    
    Process p[20] ;
    Queue q;
    init(&q);
    FILE *f ;
    int numberofp = readfile(f,&p);
    printf("Number of processes is %d\n",numberofp);
    checkbirthtime(p,&q,0);
    
    for(i=0 ; i < 16; i++)
    { if(isEmpty(&q))
    {printf("waiting\t(%d-->%d)\n",i,i+1);
        checkbirthtime(p, &q, i+1);
    }
    else
    {
        Item n = dequeue(&q);
        printf("%s\t(%d-->%d)",n->name, i, i+1 );
        n->remaining_time--;
        
        checkbirthtime(p, &q, i+1);
        checkquantum(n, &q);
        printf("\n");
    }
    }
    printf("Stop");
}
/*
 *
 */
int main(int argc, char**argv)
{
    
    if(argc!=2) {
        printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }
    RoundRobin(argv[2]);
    
    return 0;
}
