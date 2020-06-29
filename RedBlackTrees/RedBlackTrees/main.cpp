#include<iostream>
#include<fstream>
#include<algorithm>
#include<string.h>
//#define strcasecmp _stricmp
using namespace std;
class RBTNode
{
public:
    char* word;
    RBTNode* parent;
    RBTNode* right;
    RBTNode* left;
    bool color;
};
RBTNode* root = NULL;
RBTNode* create_node(const char* word)
{
    RBTNode* node = (RBTNode*)malloc(sizeof(RBTNode));
    node->word = (char*)malloc(128);
    strcpy(node->word, word);
    node->left = node->right = node->parent = NULL;
    node->color = 1;
    return node;
}
void inorder(RBTNode* root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    if (root->parent != NULL)
        cout << root->word << "  " << root->color << " " << root->parent->word << endl;
    else
        cout << root->word << "  " << root->color << endl;
    inorder(root->right);
}
void rotate_right(RBTNode*& root, RBTNode*& x)
{
    RBTNode* y = x->left;
    x->left = y->right;
    if (y->right != NULL)
    {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL)
    {
        root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->right = x;
    x->parent = y;
}
void rotate_left(RBTNode*& root, RBTNode*& x)
{
    RBTNode* y = x->right;
    x->right = y->left;
    if (y->left != NULL)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL)
    {
        root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}
int height(RBTNode* root)
{
    return root == NULL ? -1 : 1 + max(height(root->left), height(root->right));
}
RBTNode* balance_tree(RBTNode*& root, RBTNode*& node)
{
    RBTNode* parent = NULL;
    RBTNode* grand = NULL;
   // if (node->parent != NULL) {
        while ((node != root) && (node->color != 0) && (node->parent->color == 1))
        {

            parent = node->parent;
            grand = node->parent->parent;
            //if parent is right
                    //if uncle is red change colors
                    //else if child is left then  right rotate    //right left case
                    //else this means right right then change color and right rotate
            if (parent == grand->left)
            {
                RBTNode* uncle_pt = grand->right;

                if (uncle_pt != NULL && uncle_pt->color == 1)
                {
                    grand->color = 1;
                    parent->color = 0;
                    uncle_pt->color = 0;
                    node = grand;
                }

                else
                {

                    if (node == parent->right)
                    {
                        rotate_left(root, parent);
                        node = parent;
                        parent = node->parent;
                    }
                    else
                    {

                        rotate_right(root, grand);
                        grand->color = 1;
                        parent->color = 0;
                        //swap(parent_pt->color, grand_parent_pt->color);
                        node = parent;
                    }

                }
            }
            //else parent is left
                    //if uncle is red then change colors
                    //else then its left right then left rotate
                    //else if child is left then left left then change colors and right rotate on grand
            else
            {
                RBTNode* uncle = grand->left;
                if ((uncle != NULL) && (uncle->color == 1))
                {
                    grand->color = 1;
                    parent->color = 0;
                    uncle->color = 0;
                    node = grand;
                }
                else
                {

                    if (node == parent->left)
                    {
                        rotate_right(root, parent);
                        node = parent;
                        parent = node->parent;
                    }
                    else
                    {
                        rotate_left(root, grand);
                        parent->color = 0;
                        grand->color = 1;
                        node = parent;
                    }

                }
            }
        }
    
    root->color = 0;
    return root;
}
RBTNode* insert(RBTNode* root, RBTNode* node)
{
    if (root == NULL)
        return node;
    
    if (strcasecmp(node->word, root->word) < 0)
    {
        root->left = insert(root->left, node);
        root->left->parent = root;
    }
    else if (strcasecmp(node->word, root->word) > 0)
    {
        root->right = insert(root->right, node);
        root->right->parent = root;
    }
    return root;
}
int searchElement(RBTNode* root, char* str) {
    if (root == NULL)  return 0;
    else if (strcasecmp(root->word, str) == 0) return 1;
    else if (strcasecmp(root->word, str) > 0) return searchElement(root->left, str);
    else if (strcasecmp(root->word, str) < 0)  return searchElement(root->right, str);
    else return 0;
}
//void read_file()
//{
//    char word[128];
//    int counter = 0;
//    ifstream fptr("/Users/ahmedtharwatwagdy/Downloads/dictionary.txt");
//    if (!fptr.is_open())
//        cout << "Cannout Find File!" << endl;
//    while (fptr >> word)
//    {
//        RBTNode* node = create_node(word);
//        root = insert(root, node);
//        root = balance_tree(root, node);
//        counter++;
//    }
//    cout << "Height Of The Tree Is : " << height(root) << endl;
//    cout << "Size Of The Tree Is :" << counter << endl;
//
//}

void readFromFile(){
    char word[128];
    int counter = 0;
    FILE*f;
    f=fopen("/Users/ahmedtharwatwagdy/Downloads/dictionary.txt", "r");
    while (!feof(f)) {
    fscanf(f,"%[^\n]\n",word);
      RBTNode* node = create_node(word);
      root = insert(root, node);
      root = balance_tree(root, node);
      counter++;
    }
    fclose(f);
    cout << "Height Of The Tree Is : " << height(root) << endl;
    cout << "Size Of The Tree Is :" << counter << endl;
}

void menu() {
    int choice, x;
    char* str = new char[128];
    cout <<endl<< "Choose one of the following" << endl << "1-Search" << endl << "2-Insert" << endl << "0-Exit" << endl;
    cin >> choice;
    if (!choice)    exit(0);
    cout <<endl<< "Enter the text" << endl;
    cin>>str;
    cout<<endl<<str<<endl;
    cout<<endl<<root->word<<endl;
    
    x = searchElement(root, str);
    cout<<x<<endl<<endl;
    if (choice == 1) {
        x == 1 ? cout << "Element found!" << endl : cout << "Element NOT found" << endl;
        menu();
    }
    else if (choice == 2) {
        if (!x) {
            RBTNode* node = create_node(str);
            root = insert(root, node);
           cout << "Element Inserted Successfully" << endl;
        }
       else cout << "Element already exists!" << endl;
        menu();
    }

}
int main()
{
    readFromFile();
//    read_file();
    cout<<root->word<<endl;
    inorder(root);
    menu();
}
//#include<iostream>
//#include<fstream>
//#include<algorithm>
//#include<string.h>
//using namespace std;
//
//class RBTNode
//{
//public:
//    char* word;
//    RBTNode* parent;
//    RBTNode* right;
//    RBTNode* left;
//    bool color;
//};
//RBTNode* root = NULL;
//RBTNode* create_node(const char* word)
//{
//    RBTNode* node = (RBTNode*)malloc(sizeof(RBTNode));
//    node->word = (char*)malloc(128);
//    strcpy(node->word, word);
//    node->left = node->right = node->parent = NULL;
//    node->color = 1;
//    return node;
//}
//RBTNode* getRoot(){
//    while(root->parent!=NULL)   root=root->parent;
//    return root;
//}
//void inorderHelper(RBTNode* root)
//{
//    if (root == NULL)
//        return;
//    inorderHelper(root->left);
//    if (root->parent != NULL)
//        cout << root->word << "  " << root->color << " " << root->parent->word << endl;
//    else
//        cout << root->word << "  " << root->color << endl;
//    inorderHelper(root->right);
//}
//void rotate_right(RBTNode*& root, RBTNode*& x)
//{
//    RBTNode* y = x->left;
//    x->left = y->right;
//    if (y->right != NULL)
//    {
//        y->right->parent = x;
//    }
//    y->parent = x->parent;
//    if (x->parent == NULL)
//    {
//        root = y;
//    }
//    else if (x == x->parent->left)
//    {
//        x->parent->left = y;
//    }
//    else
//    {
//        x->parent->right = y;
//    }
//    y->right = x;
//    x->parent = y;
////    root=getRoot();
//
//}
//void rotate_left(RBTNode* root, RBTNode* x)
//{
//    RBTNode* y = x->right;
//    x->right = y->left;
//    if (y->left != NULL)
//    {
//        y->left->parent = x;
//    }
//    y->parent = x->parent;
//    if (x->parent == NULL)
//    {
//        root = y;
//    }
//    else if (x == x->parent->left)
//    {
//        x->parent->left = y;
//    }
//    else
//    {
//        x->parent->right = y;
//    }
//    y->left = x;
//    x->parent = y;
////    root=getRoot();
//}
//int height(RBTNode* root)
//{
//    return root == NULL ? -1 : 1 + max(height(root->left), height(root->right));
//}
//
//RBTNode* balance_tree(RBTNode* root, RBTNode*node)
//{
//    RBTNode* parent = NULL;
//    RBTNode* grand = NULL;
//    while ((node != root) && (node->color != 0) &&(node->parent->color == 1))
//    {
//
//        parent = node->parent;
//        grand = node->parent->parent;
//        //if parent is right
//                //if uncle is red change colors
//                //else if child is left then  right rotate    //right left case
//                //else this means right right then change color and right rotate
//
//        if (parent == grand->left)
//        {
//
//            RBTNode* uncle_pt = grand->right;
//
//            if (uncle_pt != NULL && uncle_pt->color == 1)
//            {
//                grand->color = 1;
//                parent->color = 0;
//                uncle_pt->color = 0;
//                node = grand;
//            }
//
//            else
//            {
//
//                if (node == parent->right)
//                {
//                    rotate_left(root, parent);
//                    node = parent;
//                    parent = node->parent;
//                }
//                else
//                {
//
//                    rotate_right(root, grand);
//                    grand->color = 1;
//                    parent->color = 0;
//                    //swap(parent_pt->color, grand_parent_pt->color);
//                    node = parent;
//                }
//
//            }
//        }
//        //else parent is left
//                //if uncle is red then change colors
//                //else then its left right then left rotate
//                //else if child is left then left left then change colors and right rotate on grand
//        else
//        {
//            RBTNode* uncle = grand->left;
//            if ((uncle != NULL) && (uncle->color == 1))
//            {
//                grand->color = 1;
//                parent->color = 0;
//                uncle->color = 0;
//                node = grand;
//            }
//            else
//            {
//
//                if (node == parent->left)
//                {
//                    rotate_right(root, parent);
//                    node = parent;
//                    parent = node->parent;
//                }
//                else
//                {
//                    rotate_left(root, grand);
//                    parent->color = 0;
//                    grand->color = 1;
//                    node = parent;
//                }
//
//            }
//        }
//    }
////    if(root->parent!=NULL)  root=root->parent;
////    root=getRoot();
//    root->color = 0;
//    return root;
//}
//
//RBTNode* insert(RBTNode* root, RBTNode* node)
//{
//    if (root == NULL)
//        return node;
//    if (strcasecmp(node->word, root->word) < 0)
//    {
//        root->left = insert(root->left, node);
//        root->left->parent = root;
//    }
//    else if (strcasecmp(node->word, root->word) > 0)
//    {
//        root->right = insert(root->right, node);
//        root->right->parent = root;
//    }
//
//    return root;
//}
//int searchElement(RBTNode* root,char*str){
//    if(root==NULL)  return 0;
//    else if (strcasecmp(root->word,str)==0) return 1;
//    else if (strcasecmp(root->word,str)>0) return searchElement(root->left,str);
//    else if (strcasecmp(root->word,str)<0)  return searchElement(root->right,str);
//    else return 0;
//
//}
//void read_file()
//{
////    RBTNode* xnode = NULL;
//    char word[128];
//    int counter = 0;
//    ifstream fptr("/Users/ahmedtharwatwagdy/Downloads/dictionary.txt");
//    if (!fptr.is_open())
//        cout << "Cannout Find File!" << endl;
//    while (fptr >> word)
//    {
//        RBTNode* node = create_node(word);
////        if (strcmp(word, "Fargo") == 0)
////        {
////            xnode = node;
////        }
//        root = insert(root, node);
//        root = balance_tree(root, node);
////        root=getRoot();
//        counter++;
//    }
////    root=getRoot();
//    cout << "Height Of The Tree Is : " << height(root) << endl;
//    cout << "Size Of The Tree Is :" << counter << endl;
//
//}
////void readFromFile(){
////    char word[128];
////    int counter = 0;
////    FILE*f;
////    f=fopen("/Users/ahmedtharwatwagdy/Documents/Data Sructure 1/assignments/BSTree/BSTree/EN-US-randomized.txt", "r");
////    while (!feof(f)) {
//////         fscanf(f,"%[^\n]s",word);
////        fgets(word, 128, f);
////        RBTNode* node = create_node(word);
////        root = insert(root, node);
////       root = balance_tree(root, node);
////       counter++;
////    }
////    fclose(f);
////    cout << "Height Of The Tree Is : " << height(root) << endl;
////    cout << "Size Of The Tree Is :" << counter << endl;
////
////
////}
//void menu(){
//    int choice,x;
//    char* str=new char[128];
//    cout<<"Choose one of the following"<<endl<<"1-Search"<<endl<<"2-Insert"<<endl<<"0-Exit"<<endl;
//    cin>>choice;
//    if(!choice)    exit(0);
//    cout<<"Enter the text"<<endl;
//    cin>>str;
////    cout<<str;
////    gets(str);
////    scanf("%[^\n]s",str);
//    x=searchElement(root, str);
//    if (choice==1){
//        x==1?cout<<"Element found!"<<endl:cout<<"Element NOT found"<<endl;
//    menu();
//    }
//    else if(choice==2){
//        if (!x) {
//            RBTNode* node = create_node(str);
//            root=insert(root, node);
//            cout<<"Element Inserted Successfully"<<endl;
//        }
//        else cout<<"Element already exists!"<<endl;
//        menu();
//    }
//
//}
//int main()
//{
//    read_file();
////    cout<<root->word<<endl;
////    readFromFile();
////    cout<<root->word<<endl;
//
//    cout<<endl<<root->word<<endl;
//    inorderHelper(root);
//    menu();
//}
