#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef union
{
    float fData;
    char* cpData;
} Item;
typedef struct
{
    Item items[100];
    int top;
} Stack;
void init(Stack *s)
{
    s->top=0;
}
int isEmpty(Stack *s)
{
    if(s->top==0)
        return 1;
    return 0;
}
Item top(Stack *s)
{
    return s->items[s->top-1];
}
Item pop(Stack *s)
{Item x;
    while(!isEmpty(s))
    {
        Item value;
        s->top--;
        value=s->items[s->top];
        return value;
    }
    return x;
}
void push(Stack *s, Item val)
{
    s->items[s->top]=val;
    s->top++;
}
void destroy(Stack *s)
{
    while(s->top!=0)
    {
        pop(s);
    }
}
void displayStack(Stack*s)
{
    Item value;
    int i;
    Stack*temp=malloc(sizeof(Stack));
    init(temp);
    for(i=0; s->top!=0; i++)
    {
        value=pop(s);
        printf("%c",value);
        push(temp,value);
    }
    printf("\n");
    while(temp->top!=0)
        push(s,pop(temp));
}
int priority(char x)
{
    switch (x)
    {
        case '+':
        case '-':
            return 0;
        case '*':
        case '/':
        case '%':
            return 1;
        case '(':
            return 2;
        case '^':
            return 3;
    }
    return -1;
}
int is_operator(char c)
{
    switch (c)
    {
        case '*':
        case '+':
        case '-':
        case '/':
        case '%':
        case '^':
            return 1;
            
        default:
            return 0;
    }
}
void infixToPostfix(char* infix, char* postfix)
{
    Stack*s=malloc(sizeof(Stack));
    char c;
    Item value;
    int i=0,j=0;
    init(s);
    
    while(infix[i]!='\0')
    {
        // c=infix[i];
        value.cpData=infix[i];
        if(isdigit(value.cpData) || value.cpData == '.' || (is_operator(value.cpData) && isdigit(infix[i+1])))
        {
            postfix[j]=value.cpData;
            j++;
        }
        else if(value.cpData=='(')
            push(s,value);
        
        else if(value.cpData==')')
        {
            
            while(top(s).cpData!='(')
            {
                postfix[j]=' ';
                postfix[++j]=pop(s).cpData;
                j++;
            }
            pop(s);
            
        }
        
        else if(is_operator(value.cpData))
        {
            postfix[j] = ' ';
            j++;
            if(isEmpty(s))
            {
                push(s,value);
            }
            else
            {
                while(!isEmpty(s)&&priority(top(s).cpData)>=priority(value.cpData)&&top(s).cpData!='(')
                {
                    if (postfix[j - 1] != ' ')
                    {
                        postfix[j] = ' ';
                        j++;
                    }
                    postfix[j]=pop(s).cpData;
                    j++;
                    postfix[j] = ' ';
                    j++;
                }
                push(s,value);
            }
        }
        //else
        // {
        //}
        i++;
    }
    while(!isEmpty(s))
    {
        if (postfix[j - 1] != ' ')
        {
            postfix[j] = ' ';
            j++;
        }
        postfix[j]=pop(s).cpData;
        j++;
        postfix[j] = ' ';
        j++;
    }
    postfix[++j]='\0';
    //  return postfix;
}
/*
 * evaluatePostfix: Evaluates an expression in postfix notation
 *                     (Reverse-Polish Notation)
 *                    ASSUME single-digit operands
 */
float evaluate(char x,float op1,float op2)
{
    Item value;
   if(x=='+')
    {
        //value.fData=op1.fData+op2.fData;
        return op1+op2;
    }
   else if(x=='-')
    {
        //value.fData=op1.fData-op2.fData;
        return op1-op2;
    }
   else if(x=='*')
    {
        //value.fData=op1.fData*op2.fData;
        return op1*op2;
    }
   else if(x=='/')
    {
        // value.fData=op1.fData/op2.fData;
        return op1/op2;
    }
   else if(x=='^')
    {
        // value.fData=pow(op1.fData,op2.fData);
        return pow(op1,op2);
    }
   else exit(0);
}
float evaluatePostfix(char* postfix)
{
    Stack*s=malloc(sizeof(Stack));
    init(s);
    int i;
    Item op1,op2,value;
    const char x[2] = " ";
    char *token;
    token = strtok(postfix, x);
    while(token!=NULL)
    {
        if(isdigit(*token) || *token == '.' || (is_operator(*token) && isdigit(token[1])))
        {
            value.fData=atof(token);
            push(s,value);
        }
        else
        {
            float op2=pop(s).fData;
            float op1=pop(s).fData;
            value.fData=evaluate(*token,op1,op2);
            push(s,value);
        }
        token = strtok(NULL, x);
    }
    value=pop(s);
    return value.fData;
    
    
    
    
    
    
    /*const char x[2] = " ";
     char *token;
     token = strtok(postfix, x);
     while(token!=NULL)
     {
     if(is_operator(token))
     {
     float op2=pop(s).fData;
     float op1=pop(s).fData;
     value.fData=*token;
     value.fData=evaluate(token,op1,op2);
     push(s,value);
     }
     else
     {
     value.fData=atof(token);
     //op2=pop(s);
     //op1=pop(s);
     //push(s,evaluate(*postfix++,op1,op2));
     push(s,value);
     }
     token = strtok(NULL, x);
     }
     value=pop(s);*/
    
}
void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}
int main()
{
    char infixExpr[256] = "";
    char postfixExpr[256] = "";
    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);
        
        infixToPostfix(infixExpr, postfixExpr);
        printf("Postfix : %s\n", postfixExpr);
        
        float result = evaluatePostfix(postfixExpr);
        printf("Result: %f\n\n", result);
        
        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    }
    return 0;
    
}
