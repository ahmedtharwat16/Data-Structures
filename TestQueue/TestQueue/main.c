//
//  main.c
//  TestQueue
//
//  Created by Ahmed Tharwat Wagdy on 3/25/19.
//  Copyright © 2019 Ahmed Tharwat Wagdy. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

/*
 * Process: Each process has a name and has an execution time.
 *          We keep track of how long the process still needs
 *          to run on the processor. "remaining_time" is the
 *          remaining execution time of the process.
 * Item: An item that is being enqueued to or dequeued from the queue
 *       It is a pointer to the process
 */
typedef struct {
    char *name;
    int remaining_time;
} Process, *Item;
/*
 *
 */
typedef struct Node {
    Item data;                      /*********/
    struct Node* next;
} Node;
/*
 *
 */
typedef struct {
    Node* head;
    Node* tail;
} Queue;
/*
 *
 */
void init(Queue *q) {
    q->head=(Node*)malloc(sizeof(Node));
    q->tail=(Node*)malloc(sizeof(Node));
    q->head=NULL;
    q->tail=NULL;
}
int isEmpty(Queue *q) {
    if(q->head==NULL&&q->tail==NULL) return 1;
    else return 0;
}


void enqueue(Queue*q, Item val) {                      /**/
    Node* x=malloc(sizeof(Node));
    x->data=val;
    x->next=NULL;
    if(isEmpty(q)){
    q->head=x;
    q->tail=x;
    }
    else
    {
        q->tail->next=x;
        q->tail=x;
    }
    
}
//Item dequeue(Queue *q)
//{
//    Node* x;
//    if (!isEmpty(q))
//    {
//        Item val = q->head->data;
//        x=q->head;
//        q->head = q->head->next;
////        q->count--;
//        //free(x);
//        return val;
//    }
//    else
//    {
//        printf("\nNULLLL");
//        return NULL;
//
//    }
//
//}
//Item dequeue(Queue*q) {                      /**/
//    Item x=malloc(sizeof(Item));
////    x->name=NULL;
////    x->remaining_time=0;
//    if(isEmpty(q))
//       printf("empty queue");
//    else
//    {
//        Node*temp=malloc(sizeof(Node));
//        temp=q->head;
//        x=temp->data;
//        q->head=q->head->next;
//        free(temp);
//      //  return x;
//    }
//    return x;
//}
void destroy(Queue *q) {
    if(isEmpty(q));
    else{
        Node*x=malloc(sizeof(Node));
        q->tail=NULL;
        while(!isEmpty(q)){
            x=q->head;
            q->head=q->head->next;
            x->next=NULL;
            free(x);
        }
    }
}
void RoundRobin(char* filename)
{
    Queue*q;
    init(q);
   Process token[5];
    FILE* f;
    f=fopen(filename, "r");
    int i=0;
    int x;
    int time=0;
    int flag =0;

    if(f!=NULL){
        while(!feof(f)){
            if(!isEmpty(q)){
               Process temp;
                temp=*dequeue(q);
                printf("%s\t(%d-->%d)",temp.name,time-1,time);
                temp.remaining_time--;
                enqueue(q, &temp);
                printf("%s",dequeue(q)->name);
                
                
            }
            if (flag==0) {
            
            fscanf(f,"%[^ ]",token[i].name);
//            printf("%s\n",token[i].name);
            fscanf(f,"%d", &x);
//            printf("%d\n",x);
            fscanf(f,"%d", &token[i].remaining_time);
//            printf("%d\n",token[i].remaining_time);
            }
            
            if(x==time) {
                if (token[i].remaining_time>0) {
                    enqueue(q,&token[i]);
                }
                else    printf("%s  exit",token[i].name);
                flag=0;
            }
            else if(x<time){
             enqueue(q, &token[i]);
               //  printf("%d",token[i].remaining_time);
               enqueue(q, dequeue(q));
//               printf("%s",dequeue(q)->name);
//                 break;
                        }
            else if(x>time){
                flag=1;
                i--;
                printf("waiting (%d-->%d)",time,time+1);
            }
            i++;
            time++;
        }
        fclose(f);
    }
    else printf("error\n\n");
}
//void RoundRobin(char* filename)
//{
//    Queue *q;
//    q = malloc(sizeof(Queue));
//    init(q);
//
//    Item o1=malloc(sizeof(Item));
//    Item tempO=malloc(sizeof(Item));
//    Item o2=malloc(sizeof(Item));
//
//    FILE *f1;
////    int d;
//    int i=0,count1=0;
//    int j =0 ;
//    char temx[7];
//    Item wait[4];
////  int tempO;
//    int tempr;
//    int x= 0;
//    f1 = fopen(filename,"r");
//    while(!feof(f1)||!isEmpty(q))
//    {
//
//
//        if(x<9){
//
//            fscanf(f1,"%s",temx);
//            o1->name=temx;
//            fscanf(f1,"%d",&i);
//            fscanf(f1,"%d",&tempr);
//            o1->remaining_time = tempr;
//            x++;
//        }
//        if(i<=count1)
//        {
//            printf("%s(%d-->%d)\n",o1->name,count1++,count1);
//            o1->remaining_time--;
//            if(o1->remaining_time==0)
//                printf("     %s halts",o1->name);
//            else
//            {   *tempO =*o1;
//                enqueue(q,tempO);
//                //  free(tempO);
//            }
//        }
//        else if(i>count1&&!isEmpty(q))
//        {
//            wait[j] = o1;
//            j++;
//            while(count1<=i)
//            {
//                o2=dequeue(q);
//                printf("\n%s(%d-->%d)",o2->name,count1++,count1);
//                o2->remaining_time--;
//                if(o2->remaining_time==0)
//                    printf("     %s halts",o2->name);
//                else
//                    enqueue(q,o2);
//            }
//        }
//        else if (i>count1){
//            wait[j] = tempO;
//            j++;
//            while(count1<i)
//                printf("\nIdle(%d-->%d)",count1++,count1);
//
//            while(o1->remaining_time!=0){
//                printf("\n%s(%d-->%d)",o2->name,count1++,count1);
//                o1->remaining_time-=1;
//            }
//
//        }
//    }
//    printf("      %s halts",o1->name);
//    printf("\n EOF!");
//    fclose(f1);
//
//}
int main() {
   RoundRobin("/Users/ahmedtharwatwagdy/Desktop/ahmed4");
    //    Queue*q;
    //    init(q);
    //    printf("%d\n",isEmpty(q));
    //    enqueue(q, 1);
    //    enqueue(q, 2);
    //    enqueue(q, 3);
    //    printf("%d\t%d\t%d\n",dequeue(q),dequeue(q),dequeue(q));
    //    destroy(q);
    //    printf("%d\t%d\t%d\n\n",dequeue(q),dequeue(q),dequeue(q));
    
    
    return 0;
}
