//
//  main.c
//  TestStack
//
//  Created by Ahmed Tharwat Wagdy on 3/22/19.
//  Copyright © 2019 Ahmed Tharwat Wagdy. All rights reserved.
//



#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef union {
    float fData;
    char* cpData;
} Item;
/*
 *
 */
typedef struct {
    Item value;                                                          /*************/
   struct Node* next;
}Node;

typedef struct {
   Node* top;
//   int  TopIndex;
} Stack;

void init(Stack *s) {
    s->top=malloc(sizeof(Node));
    s->top=NULL;

}
int isEmpty(Stack *s) {
    if(s->top==NULL)    return 1;
    else return 0;
}
Item pop(Stack *s) {                                     /*************/
    Item x;
    if(isEmpty(s)) exit(0);
    else{
        x=s->top->value;
        Node* temp=malloc(sizeof(Node));
        temp=s->top;
        s->top=s->top->next;
        temp->next=NULL;
        temp->value.cpData=NULL;
        free(temp);
       
    }
 
    return x;
}

void push(Stack *s, Item val) {                               /*************/
    Node* temp=malloc(sizeof(Node));
    temp->value=val;
    if(isEmpty(s))  {
        temp->next=NULL;
        s->top=temp;
    }
    else{
        temp->next=s->top;
        s->top=temp;
    }
 }


Item top(Stack *s) {                                              /*************/
    if(isEmpty(s))    exit(0);
    
       return  s->top->value ;
}


void destroy(Stack *s) {
    Node* temp =malloc(sizeof(Node));
    while (!isEmpty(s)) {
        temp=s->top;
        s->top=s->top->next;
        temp->next=NULL;
        temp->value.cpData=NULL;
        free(temp);
    }
}
float GetOperation(char op,float op1,float op2){
    switch (op) {
        case '+':
            return op2+op1;
            break;
        case '-':
            return op2-op1;
            break;
        case '*':
            return op2*op1;
            break;
        case '/':
            return op2/op1;
            break;
        default:return 0;
            break;
    }
    
}
//float evaluatePostfix(char* postfi)
//{
//
//    Stack* s;
//    init(s);
//    printf("%d",isEmpty(s));
//    Item x,ans;
//    char* postfix="231*+9-";
//    while(*postfix!='\0'){
//        if(isdigit(*postfix))   {
//            x.fData=*postfix-'0';
//            push(s, x);
//        }
//        else   {
//            //x.cpData=;
//           ans.fData= GetOperation(*postfix,pop(s).fData,pop(s).fData);
//            push(s, ans);
//        }
//    postfix++;
//}
//
//    return top(s).fData ;
//}


int main() {

    Stack*s;
    init(s);
    char* postfix= "231*+9-";
  
    Item x,ans;
    while(*postfix!='\0'){
       // if(isEmpty(s))  exit(0);
        if(isdigit(*postfix))   {
            x.fData=*postfix-'0';
            push(s, x);
        }
        else   {
            //x.cpData=;
            ans.fData= GetOperation(*postfix,pop(s).fData,pop(s).fData);
            push(s, ans);
        }
        postfix++;
    }
    printf("%f\n\n",pop(s).fData);
   
    
    
    //    char* x="231*+9-";
//    while(*x!='\0'){
//    printf("%c",*x);
//    x++;}
    //    float temp=*x-'0';
//    printf("%f\n ",GetOperation('/', 2, 5));
//    x++;
//     temp=*x-'0';
//    printf("%f\n ",temp);
//    x++;
//    temp=*x-'0';
//    printf("%f\n ",temp);
//    x++;
//     printf("%f",y.fData);
//     printf("%f",evaluatePostfix("231*+9-"));
//    Stack* s;
//    init(s);
//    Item x;x.fData=1.2;
//    push(s, x);
//    Item y=pop(s);
//    printf("%f",y.fData);
//    printf("%d\n",isEmpty(s));
//    push(s, 1);
//    push(s, 2);
//    push(s, 3);
//    printf("%d",top(s));
//    destroy(s);
//    printf("%d",top(s));

    //printf("%d\t%d\t%d\n\n",pop(s),pop(s),pop(s));
  
    
    return 0;
}
