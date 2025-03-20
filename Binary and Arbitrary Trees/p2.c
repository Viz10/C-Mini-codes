#include "p1.h"
///BFS DFS Traversals
static struct Queue {
	int st;
	int dr;
	Node* array[100];
};

static  void init_queue(Queue** coada) {

	*coada = malloc(sizeof(Queue));
	(*coada)->st = 0;
	(*coada)->dr = 0;
	memset((*coada)->array, 0, 100 * sizeof(Node*));
}

static int empty_queue(Queue* coada) {
	return coada->st == coada->dr;
}

static void push_queue(Queue* coada, Node* nod) {

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


#define MAX_NODES 200
static struct Node
{
	int val;
	struct Node* children[MAX_NODES]; /// holds info for all possible children -array of pointers
	int child_count;
};

static Node* createNode(int data)
{
	Node* newNode = malloc(sizeof(Node));
	newNode->val = data;
	newNode->child_count = 0;
	return newNode;
}

static void addChild(Node* parent, Node* child)
{
	parent->children[parent->child_count++] = child; /// add children node to parrent`s array
}

static void DFS(Node* current)
{
	if (current == NULL) return;

	printf("%d ", current->val); /// print root
	for (int i = 0; i < current->child_count; i++)
	{
		DFS(current->children[i]); /// print  in depth
	}
}

static void freeTree(Node* root)
{
	if (root == NULL) return;

	for (int i = 0; i < root->child_count; i++)
	{
		freeTree(root->children[i]);
	}

	free(root);
}

static void create_tree(Queue*coada,Node* root, int n,int*vec)
{
	if (root == NULL)
	{
		return;
	}

	push_queue(coada, root);

	while (!empty_queue(coada))
	{
		Node* top = top_queue(coada);

		for (int i = 0; i < n; ++i) /// parcurgere vec tati pt a baga copii
		{
			if (vec[i] == top->val) // children
			{
				Node* child = createNode(i + 1);
				addChild(top, child);
				push_queue(coada,child);
			}
		}
		pop_queue(coada);
	}
}
 
static void BFS(Queue* coada,Node* root) {

	
	if (root == NULL) {
		return;
	}

	int cnt = 0;
	push_queue(coada,root);

	while (!empty_queue(coada)) {

		int nr = coada->dr - coada->st;
		printf("niv %d: ", cnt);

		for(int l=0;l<nr;++l){

		Node* top = top_queue(coada);
		printf("%d ", top->val);
		for (int i = 0; i < top->child_count; ++i) { /// it will perform nr times the pop and pushed 
			push_queue(coada,top->children[i]);
		}
		pop_queue(coada);
		}
		cnt++;
		printf("\n");
	}

}

static void addNode(Node* parent, int data) {
	// Create a new node
	Node* newNode = createNode(data);

	// Add the new node to the parent's children
	addChild(parent, newNode);
}

static void DFS_ADD(Node* current, int data,int newval) {
	if (current == NULL) return;

	// If the current node is the one where we want to add
	if (current->val == data) {
		// Create a new node
		Node* newNode = createNode(newval);
		// Add the new node as a child of the current node
		addChild(current, newNode);
	}

	// Recurse on the children
	for (int i = 0; i < current->child_count; ++i)
		DFS_ADD(current->children[i], data, newval);
}


void ex2() {

	///              1  2  3  4  5  6  7  8  9  10
	int parent[] = { 0, 1, 1, 2, 2, 3, 3, 5, 5, 5 };
	Queue* coada;
	init_queue(&coada);

	int n = sizeof(parent) / sizeof(parent[0]);
	Node* root = NULL;

	for (int i = 0; i < n; ++i)
		if (parent[i] == 0)
			root = createNode(i+1); /// search for root and create it

	create_tree(coada,root, n, parent);

	addNode(root, 1000);
	n++;
	DFS_ADD(root, 8, 500);


	memset(coada->array,0,100);
	coada->st = coada->dr = 0;

	BFS(coada,root);
	printf("\n");
	DFS(root);
	freeTree(root);
	free(coada);
}