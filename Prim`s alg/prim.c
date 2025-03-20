#include "prim.h"

/// implementare cu vector de liste de noduri adj
/// O(N^2)

struct Node
{

    int node_nr;
    int len;
    Node* next;

};

struct Graph
{

    int nr_nodes;
    Node** array;

};

void init_graph(Graph** graf,int n)
{

    if (*graf != NULL) return;

    *graf = malloc(sizeof(Graph)); /// create graph class on heap

    (*graf)->nr_nodes = n;
    (*graf)->array = calloc(n+1, sizeof(Node*)); /// create on heap ,array of pointers to nodes , which will be array of linked lists (adj nodes) of a node

}

Node* create_node(int n)
{

    Node* aux = malloc(sizeof(Node));
    aux->next = NULL;
    aux->node_nr = n;
    return aux;

}

void add_node(Graph* graf, int dest, int nou,int len)
{

    Node* aux = create_node(nou);
    aux->len = len;
    aux->next = graf->array[dest]; /// add to begining of list of adj nodes
    graf->array[dest] = aux;

}

void alg(Graph*graf,bool*pus,int*parinte,int*min,int*rez,int start)
{


    pus[start] = true;
    parinte[start] = -1; /// primul e vizitat si pus

    int cnt = 1;
    int to_be_put=-1,father=-1;

    while (cnt != graf->nr_nodes)   /// all nodes must be added
    {

        for (int i = 1; i <= graf->nr_nodes; ++i)
        {
            /// check current visited nodes
            if (pus[i])
            {

                Node* aux = graf->array[i];
                while (aux)
                {
                    /// check adj nodes that havent been marked for min path
                    if (!pus[aux->node_nr])
                    {

                        if (aux->len < *min)
                            *min = aux->len,to_be_put=aux->node_nr,father=i;

                    }
                    aux = aux->next;
                }
            }
        }

        (*rez) += (*min); /// add min length to total sum
        pus[to_be_put] = true; /// mark added adj node as visited
        parinte[to_be_put] =father; ///mark source node as father
        (*min) = 100000; /// reset min for next search
        to_be_put = -1, father = -1;
        cnt++;
    }

}
int weight(Graph* graf, int parinte, int i)   /// return weight between parent node and noe
{

    Node* aux = graf->array[parinte];
    while (aux)
    {
        if (aux->node_nr == i)   /// found node
        {
            return aux->len; /// ret lenght
        }
        aux = aux->next;
    }
    return -1; /// edge not found
}

void prin_MST(Graph*graf,int*parinte,int rez, FILE* fout)
{
    fprintf(fout, "minimum spanning tree length:%d\n", rez);

    for (int i = 1; i <= graf->nr_nodes; ++i)
    {
        if (parinte[i] != -1)
        {
            int weight1 = weight(graf, parinte[i], i);
            fprintf(fout, "Edge: %d <-> %d, Weight: %d\n", parinte[i], i, weight1);
        }
    }
}

typedef struct pereche
{

    int cap;
    int coada;

} pereche;

void afis(Graph* graf)   /// afiseaza 3 5 o data , nu mai afiseaza 5 3 iara ,este undirected graph...
{

    pereche viz[21]; /// vector de perechi
    int cnt = 0;

    for (int i = 1; i <= graf->nr_nodes; ++i)
    {

        if (graf->array[i] != NULL)
        {

            Node* aux = graf->array[i];
            while (aux)
            {

                int ok = 0;
                for (int j = 1; j <= cnt; ++j)   /// parcurgere vector de muchii afisate
                {
                    if ((viz[j].cap == i && viz[j].coada == aux->node_nr) || (viz[j].cap == aux->node_nr && viz[j].coada == i))
                    {
                        ok = 1; /// apare deja
                        break; /// nu mai afisam
                    }
                }

                if (ok == 0)
                {
                    printf("(%d <-> %d, pondere: %d), ", i, aux->node_nr, aux->len);
                    viz[++cnt].cap = i;
                    viz[cnt].coada = aux->node_nr;
                }

                aux = aux->next;
            }
            printf("\n");
        }
    }

}

void dealloc(Graph** graf)
{
    for (int i = 1; i <= (*graf)->nr_nodes; ++i)
    {
        if ((*graf)->array[i] != NULL)
        {
            Node* aux = (*graf)->array[i];
            while (aux->next != NULL)
            {
                Node* next = aux->next;
                free(aux);
                aux = next;
            }
            free(aux);
        }
    }
    free((*graf)->array);
    (*graf)->nr_nodes = 0;
    free(*graf);
    *graf = NULL;
}

void prim()
{

    Graph* graf = NULL;

    FILE* fin = fopen("prim.in", "r");
    FILE* fout = fopen("prim.out", "w");

    if (fin == NULL || fout == NULL)
    {
        printf("error opening file");
        exit(2);
    }

    int a, b, c;

    fscanf(fin,"%d\n", &a); /// read nr of nodes
    init_graph(&graf, a);

    while (fscanf(fin, "%d %d %d\n", &a, &b,&c) > 0)   /// read nodes and their length between them
    {

        add_node(graf, a, b, c);
        add_node(graf, b, a, c);

    }

    afis(graf);

    bool* pus=NULL;
    int* parinte = NULL;

    pus = calloc(graf->nr_nodes + 1, sizeof(bool));
    parinte= calloc(graf->nr_nodes + 1, sizeof(int));

    int min = 100000, rez = 0;

    alg(graf,pus,parinte,&min,&rez,2);
    prin_MST(graf, parinte, rez,fout);

    dealloc(&graf);
    free(pus);
    free(parinte);

    fclose(fin);
    fclose(fout);
}
