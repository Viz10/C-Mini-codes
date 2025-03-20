#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node
{
    char val;
    struct _node *stanga;
    struct _node *dreapta;
} node;

node*create_node(char val)
{
    node* nod=calloc(1,sizeof(node));
    nod->stanga=NULL;
    nod->dreapta=NULL;
    nod->val=val;
    return nod;
}

void create_preorder(node** root,char *arr,int *poz,int len) {

	int ok = 1;

	if (arr == NULL || *poz==len) return;

	if (arr[*poz] =='*') {
		(*poz)++;
		ok = 0;
	}

	if (ok) {
		*root = create_node(arr[*poz]);
		(*poz)++;
	}

	if (*root != NULL) {
		create_preorder(&((*root)->stanga), arr, poz,len);
		create_preorder(&((*root)->dreapta), arr, poz ,len);
	}
}

void preorder_afis(node *p)
{
    if (p != NULL)
    {
        printf("%c ", p->val);
        preorder_afis(p->stanga);
        preorder_afis(p->dreapta);
    }
}

void prob1()
{
    FILE*fin=fopen("data.in","r");

    char preorder[200];
    node*root;
    int poz=0;

    if(fin==NULL)
    {
        printf("failed to open file");
        exit(1);

    }

    char ch;
    int i=0;
    while((ch=fgetc(fin))!='\n')
    {
        preorder[i++]=ch; /// put char in vec
    }

    create_preorder(&root,preorder,&poz,i);

    preorder_afis(root);
}
