#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 200

typedef struct Node
{
    int data;
    struct Node* children[MAX_NODES]; /// holds info for all possible children -array of pointers
    int child_count;
} Node;

Node* createNode(int data)
{
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->child_count = 0;
    return newNode;
}

void addChild(Node* parent,Node*child)
{
    parent->children[parent->child_count++] = child; /// add children node to parrent`s array
}

void printTree(Node* root)
{
    if (root == NULL) return;

    printf("%d ", root->data); /// print root
    for (int i = 0; i < root->child_count; i++)
    {
        printTree(root->children[i]); /// print  in depth
    }
}

void freeTree(Node* root)
{
    if (root == NULL) return;

    for (int i = 0; i < root->child_count; i++)
    {
        freeTree(root->children[i]);
    }

    free(root);
}

void fun(Node*root,int n,int*parent)
{
    if(root==NULL){
        return NULL;
    }

    for(int i=0; i<n; ++i)
    {
        if(parent[i]!=0) /// if not root
        {
            if(parent[i]==root->data) /// children
            {
                addChild(root,createNode(i+1));
            }


        }
    }
    for(int i=0; i<root->child_count; ++i)
        fun(root->children[i],n,parent); /// advance to children as father
}

/*

In this version, we use a queue to hold nodes that we need to process. For each node, we check if it is the parent of any nodes in the parent array. If it is, we create a child node, add it to the parent, and push it onto the queue. This way, we ensure that all nodes are processed in breadth-first order, which can be more efficient than the depth-first approach in your original code. This is especially true if the tree is very deep, as it avoids the potential for stack overflow errors. #include <queue>

void fun(Node* root, int n, int* parent)
{
    if (root == NULL)
    {
        return;
    }

    std::queue<Node*> q;
    q.push(root);

    while (!q.empty())
    {
        Node* temp = q.front();
        q.pop();

        for (int i = 0; i < n; ++i)
        {
            if (parent[i] == temp->data) // children
            {
                Node* child = createNode(i + 1);
                addChild(temp, child);
                q.push(child);
            }
        }
    }
}

*/

void prob2()
{
    ///             1  2  3  4  5  6  7  8  9  10
    int parent[] = {0, 1, 1, 2, 2, 3, 3, 5, 5, 5};

    int n = sizeof(parent) / sizeof(parent[0]);
    Node*root=NULL;

    for(int i=0; i<n; ++i)
        if(parent[i]==0)
            root=createNode(i+1); /// search for root

    fun(root,n,parent);

    printTree(root);
    freeTree(root);
}
