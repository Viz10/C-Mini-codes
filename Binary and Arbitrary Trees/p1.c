#include "p1.h"
/// construct tree in multiple ways
static struct Node {
	int val;
	struct Node* stanga;
	struct Node* dreapta;
};

static struct Queue {
	int st;
	int dr;
	Node* array[100];
};


static void init_queue(Queue** coada) {

	*coada = malloc(sizeof(Queue));
	(*coada)->st = 0;
	(*coada)->dr = 0;
	memset((*coada)->array, 0, 100 * sizeof(Node*));
}

static int empty_queue(Queue* coada) {
	return coada->st == coada->dr;
}


static void push_queue(Queue* coada, Node*nod) {

	coada->array[coada->dr] = nod;
	coada->dr++;

}


static void pop_queue(Queue* coada) {

	coada->array[coada->st] = NULL;
	coada->st++;

}


static Node* top_queue(Queue* coada) {
	return coada->array[coada->st];
}


static Node*create_nod(int val)
{

	Node* newnod = malloc(sizeof(Node));
	newnod->stanga = NULL;
	newnod->dreapta = NULL;
	newnod->val = val;

	return newnod;

}

static void preorder(Node* root) {

	if (root != NULL) {
		printf("%d ",root->val);
		preorder(root->stanga);
		preorder(root->dreapta);
	}
}

void kSmallestUtil(struct node* root, int* k, int* sum) {
    if (root == NULL || *k <= 0)
        return;
    kSmallestUtil(root->left, k, sum);
    if (*k > 0) {
        *sum += root->key;
        *k -= 1;
    }
    kSmallestUtil(root->right, k, sum);
}



bool hasPathSum(TreeNode root, int targetSum) {
        if(root == null) return false;
        if(root.left == null && root.right == null) return targetSum - root.val == 0
        return hasPathSum(root.left, targetSum - root.val) || hasPathSum(root.right, targetSum - root.val);
}


static void problem(Queue* coada, Node** root,int*arr,int n) {

	int k = 0;
	if (arr[k] == -1) {
		exit(1);
	}

	*root = create_nod(arr[k]);
	k++;

	push_queue(coada,(*root));

	while (!empty_queue(coada)) {


		if (k == n) {
			break;
		}

		Node* top = top_queue(coada);

		if (arr[k] != -1) 
		{
		Node* newst = create_nod(arr[k]);
		top->stanga = newst;
		push_queue(coada, newst);
		}

		k++;
		
		if (arr[k] != -1)
		{
			Node* newdr = create_nod(arr[k]);
			top->dreapta = newdr;
			push_queue(coada, newdr);
		}

		k++;

	    pop_queue(coada);
		
	}

}


#define COUNT 7
static void print_tree(Node* root, int space)
{
	// Base case
	if (root == NULL)
		return;

	// Increase distance between levels
	space += COUNT;

	// Process right child first
	print_tree(root->dreapta, space);

	// Print current node after space
	// count
	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	printf("%d\n", root->val);

	// Process left child
	print_tree(root->stanga, space);
}

static void afis_nivel(Queue* coada, Node* root)
{
	if (root == NULL)
		return;

	push_queue(coada, root);
	int niv = 0;

	while (!empty_queue(coada))
	{
		printf("Level %d: ", niv);
		int level_size = coada->dr - coada->st; // Number of nodes at current level = nr of nodes in current queue

		for (int i = 0; i < level_size; i++) /// process number of nodes in queue
		{
			Node* aux = top_queue(coada);
			printf("%d ", aux->val);
			pop_queue(coada);

			if (aux->stanga != NULL)
			{
				push_queue(coada, aux->stanga);
			}
			if (aux->dreapta != NULL)
			{
				push_queue(coada, aux->dreapta);
			}
		}

		printf("\n");
		niv++;
	}
}

static void create_preorder(Node** root,int *arr,int *poz,int len) {

	int ok = 1;

	if (arr == NULL || *poz==len) return; /// end

	if (arr[*poz] == -1) {
		(*poz)++;
		ok = 0;
	}

	if (ok) {
		*root = create_nod(arr[*poz]); /// process node
		(*poz)++;
	}

	if (*root != NULL) {
		create_preorder(&((*root)->stanga), arr, poz,len); /// preorder
		create_preorder(&((*root)->dreapta), arr, poz ,len);
	}
}
/*
static Node* merge(Node* root1, Node* root2) {

	if (root1 == NULL)
		return root2;

	if (root2 == NULL)
		return root1;

	root1->val += root2->val;

	root1->stanga = merge(root1->stanga, root2->stanga);
	root1->dreapta= merge(root1->dreapta, root2->dreapta);

	return root1;
}
*/


static Node* merge_new_tree(Node* root1, Node* root2) {
	if (root1 == NULL && root2 == NULL)
		return NULL;

	int val = 0;
	if (root1 != NULL)
		val += root1->val;
	if (root2 != NULL)
		val += root2->val;

	Node* new_node = create_nod(val);

	if (root1 == NULL) {
		new_node->stanga = merge_new_tree(NULL, root2->stanga);
		new_node->dreapta = merge_new_tree(NULL, root2->dreapta);
	}
	else if (root2 == NULL) {
		new_node->stanga = merge_new_tree(root1->stanga, NULL);
		new_node->dreapta = merge_new_tree(root1->dreapta, NULL);
	}
	else {
		new_node->stanga = merge_new_tree(root1->stanga, root2->stanga);
		new_node->dreapta = merge_new_tree(root1->dreapta, root2->dreapta);
	}

	return new_node;
}


static void free_tree_post_order(Node** tree) {
		if ((*tree) != NULL) {
		free_tree_post_order(&((*tree)->stanga));
		free_tree_post_order(&((*tree)->dreapta));
		free(*tree);
		*tree = NULL;
	}
}
void ex1()
{
	Queue* coada1;
	Queue* coada2;
	Queue* coada3;

	Node* root1 = NULL;
	Node* root2 = NULL;
	Node* merged = NULL;

	int vec1[] = {1,2,3,4,5,-1,-1,-1,-1,-1,7,10,-1}; /// level
	int vec2[] = {1,2,10,-1,-1,11,-1,-1,3,4,-1,5}; /// preorder

	int n1 = sizeof(vec1) / sizeof(int);
	int n2 = sizeof(vec2) / sizeof(int);
	int poz = 0;

	init_queue(&coada1);
	init_queue(&coada2);
	init_queue(&coada3);

	/// met 1 
	problem(coada1, &root1, vec1, n1); 
	print_tree(root1,0);
	printf("\n\n");
	preorder(root1);
	printf("\n\n");
	afis_nivel(coada2, root1);
	
	/////////////////////////////////////////////

	create_preorder(&root2, vec2, &poz, n2); /// met 2
	print_tree(root2,0);
	printf("\n\n");
	preorder(root2);
	printf("\n\n");
	afis_nivel(coada2, root2);

	////////////////////////////////////////////////

	printf("NEW TREE:\n");

	merged = merge_new_tree(root1, root2);
	print_tree(merged, 0);
	printf("\n\n");
	preorder(merged);
	printf("\n\n");
	afis_nivel(coada3, merged);
	
	free_tree_post_order(&root1);
	free_tree_post_order(&root2);
	free_tree_post_order(&merged);
	
	free(coada1);
	free(coada2);
	free(coada3);

}