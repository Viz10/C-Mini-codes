#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{

    int val;
    struct Node *left;
    struct Node *right;

} Node;

Node*create_nod(int val)
{

    Node*newnod=malloc(sizeof(Node));
    newnod->left=NULL;
    newnod->right=NULL;
    newnod->val=val;

    return newnod;

}
void create_tree(Node**root,int val) /// i`ve decided to use a binary search tree to implement the functions
{

    if(*root==NULL)
    {
        *root=create_nod(val); /// in bases cases always return wheather just return or a val
        return;
    }

    if(val<(*root)->val)
    {
        create_tree(&((*root)->left),val);
    }

    else
    {
       create_tree(&((*root)->right),val);
    }

}

void print_tree(Node *root, int space)  /// fancy print
{
    int i;

    if (root == NULL)
        return;

    space += 5;

    print_tree(root->right, space);

    printf("\n");
    for (i = 5; i < space; i++)
        printf(" ");
    printf("%d\n", root->val);

    print_tree(root->left, space);
}

int max(int a,int b)
{
    return (a>b)?a:b;
}

int height(Node*root)
{

    if(root==NULL)
    {
        return -1; /// -1 because height for a leaf node should be 0
    }

    int left = height(root->left); /// left subtree
    int right = height(root->right); /// right subtree

    return max(left,right)+1; /// + 1 for the root of the whole tree

}
int nr_leaves(Node*root)
{

    if(root==NULL)
        return 0 ;

    if(root->left == NULL && root->right==NULL)
        return 1;  /// leaf

    return nr_leaves(root->left)+nr_leaves(root->right); /// sum recursive

}

void mirror(Node*root)
{

    if(root==NULL)
    {
        return;
    }
    else
    {
        /// subtrees
        mirror(root->left);
        mirror(root->right);

        ///swap chilren
        Node*aux=root->left;
        root->left=root->right; /// if its a leaf root , it wont affect as it will change NULL with NULL
        root->right=aux;
    }

}

void preorder(Node*root)
{
    if(root!=NULL)
    {
        printf("%d ",root->val);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(Node*root)
{
    if(root!=NULL)
    {
        inorder(root->left);
        printf("%d ",root->val);
        inorder(root->right);
    }
}

void postorder(Node*root)
{

    if(root!=NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ",root->val);
    }
}

void deallocate_tree(Node **root)
{

    if (*root == NULL)
        return;

    deallocate_tree(&(*root)->left);
    deallocate_tree(&(*root)->right);

    free(*root);
    *root=NULL;
}

int main()
{
    Node*root=NULL;

    create_tree(&root,5);
    create_tree(&root,4);
    create_tree(&root,6);
    create_tree(&root,7);
    create_tree(&root,1);
    create_tree(&root,2);
    create_tree(&root,0);
    create_tree(&root,22);
    create_tree(&root,24);
    create_tree(&root,21);

    print_tree(root,0);

    printf("\n\n\n");

    printf("nr of leaves:%d\n",nr_leaves(root));
    printf("height:%d",height(root));

    printf("\n\nafter mirrored:");
    mirror(root);
    print_tree(root,0);

    printf("\n\npreorder:");
    preorder(root);

    printf("\n\ninorder:");
    inorder(root);

    printf("\n\npostorder:");
    postorder(root);
    printf("\n");

    deallocate_tree(&root);
    return 0;
}
