//
//  main.c
//  BSTree
//
//  Created by Ahmed Tharwat Wagdy on 4/25/19.
//  Copyright © 2019 Ahmed Tharwat Wagdy. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node{
   char *data;
   struct  Node* left;
   struct  Node* right;
}Node;
Node* createNode(char* data){
    Node* x=(Node*)malloc(sizeof(Node));
    x->data=malloc(sizeof(char)*100);
    strcpy(x->data, data);
    x->left=NULL;
    x->right=NULL;
    return x;
}
int isEmpty(Node*root){
    return (root==NULL);
}
int max(int x,int y){
    return (x>y)?x:y;
}
int height(Node* root){
    if(root==NULL)   return -1;
    else return 1+max(height(root->left),height(root->right));
}
int size(Node* root){
    return (root==NULL)?0:1+size(root->left)+size(root->right);
}
int isLeaf(Node* node){
    return (node->left==NULL)&&(node->right==NULL);
}
Node* insert(Node* node,char* data){
    if(node==NULL)  node=createNode(data);
    else if(strcmp(data, node->data)<0)
            node->left=insert(node->left,data);
    else if(strcmp(data, node->data)>0)
            node->right=insert(node->right, data);
   
    return node;
}
Node* readFromFile(Node* root,char* filename){
    root=NULL;
    FILE* f;
    char c[100];
    f=fopen(filename, "r");
    while (!feof(f)) {
        fscanf(f,"%s\n",c);
        root=insert(root, c);
    }
    fclose(f);

    return root;
}
int search(Node*root,char*str,Node**lastP){
    
    if(root!=NULL&&isLeaf(root))   *lastP=root;
    if(root==NULL)    return 0;
    else if(strcmp(root->data,str)==0) return 1;
    else if(strcmp(root->data, str)>0&&root->left!=NULL)  return search(root->left, str,lastP);
    else if(strcmp(root->data, str)<0&&root->right!=NULL)  return search(root->right, str,lastP);
    else {
        *lastP=root;
        return 0;
    }
}
Node* minValue(Node* node){
    while (node->left!=NULL) {
       node=node->left;
    }
    return node;
}
Node* getSuccessor(Node*root,Node*node){
    if(node->right!=NULL)   return minValue(node->right);
    Node* successor=NULL;
    while (root!=NULL) {
        if(strcmp(node->data,root->data)<0){
            successor=root;
            root=root->left;
        }
        else if(strcmp(node->data, root->data)>0){
            root=root->right;
        }
        else break;
    }
    if(successor==NULL) successor=node;
    return successor;
}
Node* maxValue(Node* node){
    while (node->right!=NULL) {
        node=node->right;
    }
    return node;
}
Node*getPredecessor(Node*root,Node*node){
    if(node->left!=NULL)    return maxValue(node->left);
    Node*predecessor=NULL;
    while(root!=NULL){
        if(strcmp(node->data, root->data)>0){
             predecessor=root;
             root=root->right;
        }
        else if(strcmp(node->data, root->data)<0){
            root=root->left;
        }
        else break;
    }
    if(predecessor==NULL)predecessor=node;
    return predecessor;
}
void check(Node*root,char str[100]){
    Node*last;
    if(search(root,str,&last)) {
        printf("%s -CORRECT\n",str);
    }
    else {
        printf("%s -%s,%s,%s\n",str,last->data,getSuccessor(root, last)->data,getPredecessor(root, last)->data);
    }
}
int main() {
    char str[100];
    Node*root;
    root =readFromFile(root,"/Users/ahmedtharwatwagdy/Documents/C++/BSTree/BSTree/EN-US-randomized.txt");
    printf("The size of the Tree:%d\n",size(root));
    printf("The lenght of the Tree:%d\n",height(root));
    printf("Entered sentence:\t");
    scanf("%[^\n]",str);
    char*token =strtok(str, " ");
    while(token!=NULL){
    check(root,token);
        token=strtok(NULL, " ");
    }
    return 0;
}
