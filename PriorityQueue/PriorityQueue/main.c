
#include <stdio.h>
#include <stdlib.h>
/*
 * Item: Each Item has a customer name and a balance.
 *       and an integer order(it is used to handle the case when two items have same priority)
 */
typedef struct
{
    char* cName;
    double balance;
    int order;
}Item;
/*
 * Heapify index i in array of Items with size n
 */
int hasChildren(int i,int size){
    if((2*i)>size) return 0;
    else    return 1;
}

void max_heapify(Item *arr, int n, int i)
{   Item temp;
//    n=fillArrayFromFile("/Users/ahmedtharwatwagdy/Desktop/PriorityQueue.txt",arr);
//    i=n;
    if(i>0){
    if(hasChildren(i, n)){
        if(arr[i].balance<arr[2*i+1].balance){
            temp=arr[i];
            arr[i]=arr[2*i+1];
            arr[2*i+1]=temp;
            max_heapify(arr, n, 2*i+1);
    }
    if(arr[i].balance<arr[2*i].balance){
        temp=arr[i];
        arr[i]=arr[2*i];
        arr[2*i]=temp;
        max_heapify(arr, n, 2*i);
    }
        if(arr[i].balance==arr[2*i+1].balance){
            if(arr[2*i+1].order<arr[i].order){
                temp=arr[i];
                arr[i]=arr[2*i+1];
                arr[2*i+1]=temp;
                max_heapify(arr, n, 2*i+1);
            }
        }
        if(arr[i].balance==arr[2*i].balance){
            if(arr[2*i].order<arr[i].order){
                temp=arr[i];
                arr[i]=arr[2*i];
                arr[2*i]=temp;
                max_heapify(arr, n, 2*i);
            }
        }
    }
//    max_heapify(arr, n, --i);
    }

//    else    max_heapify(arr, n, n-1);
}
/*
 * Construct Priority queue from the given array of Items with size n(Build Max Heap)
 */
void construct_PQ(Item*arr,int n)
{   int i;
    for(i=n;i>0;i--){
        max_heapify(arr, n, i);

    }
}
/*
 * delete the item with max priority and then return it.
 */
void maintain_PQ(Item*arr,int n,int i){
//    int i=1;
    if(hasChildren(i, n)){
        if(arr[2*i].balance>arr[2*i+1].balance) {
            arr[i]=arr[2*i];
         maintain_PQ(arr,n,2*i);
        }
        else if(arr[2*i].balance<arr[2*i+1].balance)   {
            arr[i]=arr[2*i+1];
             maintain_PQ(arr,n,2*i+1);
        }
        else if(arr[2*i].balance==arr[2*i+1].balance){
            
            if(arr[2*i].order<arr[2*i+1].order){
                arr[i]=arr[2*i];
                maintain_PQ(arr,n,2*i);
            }
            else{
                arr[i]=arr[2*i+1];
                maintain_PQ(arr,n,2*i+1);
            }
        }
        
    }
    else if(i!=n)   arr[i]=arr[n];
}
Item extract_maximum(Item*arr,int n)
{
    Item x=arr[1];
 maintain_PQ(arr,n,1);
    return x;
}
/*
 * read array of items from file in arr and return its size.
 */
int fillArrayFromFile(char*fname,Item*arr)
{
//    arr= malloc(sizeof(Item)*100);
    FILE*f = fopen(fname, "r");
    if(f==NULL) return 0;
    int i=1;
    while(!feof(f)){
    arr[i].cName=malloc(sizeof(char)*100);
    fscanf(f,"%s ",arr[i].cName);
    fscanf(f,"%lf",&arr[i].balance);
        arr[i].order=i;

        i++;
    }
   
   
    return i;
}
/*
 * print customer names in decreasing order according their priority.
 */
void printCustomersbyPriority(Item*arr,int n)
{   Item x;
    int i=1,j=n;
    for(i;i<n;i++){
        x=extract_maximum(arr, j);
        printf("%s\t%lf\t%d\n",x.cName,x.balance,x.order);
//        j--;

    }
}
/*
 *
 */
int main(int argc, char**argv) {

        if(argc!=2) {
        printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }
    Item *customers=(Item*)malloc(sizeof(Item)*1000);
    int arrLength=fillArrayFromFile(argv[1],customers);
    construct_PQ(customers,arrLength);
    printCustomersbyPriority(customers,arrLength);
    return 0;
}


