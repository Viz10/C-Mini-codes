#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node_type
{
    int data;

    struct node_type* left;
    struct node_type* right;
} BSTNode;

BSTNode* createNode(int data)
{
    BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node into the binary search tree
BSTNode* insert(BSTNode* root, int data)
{
    if (root == NULL)
    {
        return createNode(data);
    }

    if (data < root->data)
    {
        root->left = insert(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = insert(root->right, data);
    }

    return root;
}

void preorderTraversal(BSTNode* root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}


void inorderTraversal(BSTNode* root)
{
    if (root != NULL)
    {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int stop = 0;

void inorder(BSTNode* root,int *min,int*max,int k,int *cnt,int *ok,int *current_cnt)
{
    if (root == NULL || stop==1)
        return;

        inorder(root->left,min,max,k,cnt,ok,current_cnt);
        if(stop!=1)
        {

            (*cnt)++;

            if(root->data==k && *ok!=1)
            {
                *ok=1;
                *current_cnt=*cnt;
                if(*cnt==1)
                {
                    *min=root->data;
                }
            }

            if((*ok)!=1)
            {
                *min=root->data;
                *max=root->data;
            }

            if((*ok)==1 && (*current_cnt)!=(*cnt))
            {
                *max=root->data;
                stop = 1;
                return;
            }

            if((*ok)==1 && (*current_cnt)==(*cnt))
            {
                *max=root->data;
            }
        }
        inorder(root->right,min,max,k,cnt,ok,current_cnt);

}

void print_tree(BSTNode*root, int space)  /// fancy print
{
    int i;

    if (root == NULL)
        return;

    space += 5;

    print_tree(root->right, space);

    printf("\n");
    for (i = 5; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);

    print_tree(root->left, space);
}

int main()
{

    BSTNode* root = NULL;
    root = insert(root,6);
    root = insert(root,4);
    root = insert(root,8);
    root = insert(root,2);
    root = insert(root,5);
    root = insert(root,7);
    root = insert(root,3);


    print_tree(root,5);

    printf("\n");
    int min=0,max=0,cnt=0,current_cnt=0,ok=0;
    inorder(root,&min,&max,8,&cnt,&ok,&current_cnt);
    if(ok==0)
    {
        max=min=0;
    }
    printf("%d %d\n",min,max);

    //cnt=0,ok=0;
    //inorder(root,&min,&max,5,&cnt,ok,current_cnt);
    //printf("%d %d",min,max);
    return 0;
}
