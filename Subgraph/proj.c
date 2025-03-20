#include "header.h"

struct Node
{
    int val;
    Node* next;
};

struct Graph
{
    int cnt;
    Node** array;
};

void init(Graph** graf, int n)
{
    if (*graf != NULL)
        return;

    (*graf) = malloc(sizeof(Graph));

    (*graf)->cnt = 0;
    (*graf)->array = calloc(n + 1, sizeof(Node*)); /// array points to an array of pointers to Nodes

}

Node* create_nod(int val)
{
    Node* newnode = malloc(sizeof(Node));
    newnode->next = NULL;
    newnode->val = val;

    return newnode;
}

void insert(Graph* graf, int a, int b)
{
    Node* newnod = create_nod(b);
    graf->cnt++;

    if (graf->array[a] == NULL)   /// no nodes
    {
        graf->array[a] = newnod;

    }
    else
    {
        newnod->next = graf->array[a]; /// add to beginning
        graf->array[a] = newnod;
    }
}

void dealloc(Graph* graf, int n)
{
    for (int i = 1; i <= n; ++i)
    {
        if (graf->array[i] != NULL)
        {
            Node* aux = graf->array[i];
            while (aux->next != NULL)
            {
                Node* next = aux->next;
                free(aux);
                graf->cnt--;
                aux = next;
            }
            free(aux);
        }
    }
    free(graf->array);
}

void afis(Graph* graf, int maxi, FILE* fout)
{
    fputs("graph:\n",fout);
    for (int i = 1; i <= maxi; ++i)
    {
        if (graf->array[i] != NULL)
        {
            fprintf(fout, "%d.  ", i);
            Node* aux = graf->array[i];
            while (aux != NULL)
            {
                fprintf(fout, "%d ", aux->val);
                aux = aux->next;
            }
            fprintf(fout, "\n");
        }
        else
            fprintf(fout, "%d.  ---\n", i);
    }
    fprintf(fout,"nr of nodes: %d\n", graf->cnt);
}

void print_arcs_subgraph(Graph* graf, bool*subgraf,int maxi,FILE*fout) {

    bool ok = false;

    for (int i = 1; i <= maxi; ++i) {

        if (graf->array[i] != NULL) 
            if (subgraf[i] == 1) { /// face parte din subgraf , trb sa afisam arcele fix la nodurile  din aceelasi subgraf

                Node* aux = graf->array[i]; /// root of list of adjacent nodes
                while (aux != NULL)
                {
                    if (subgraf[aux->val] == 1) { /// node also in subgraf

                        if (!ok) {
                            fprintf(fout,"V` arcs ");
                            ok = true;
                        }

                        fprintf(fout,"(%d %d) ",i, aux->val); /// i put the nodes at the beginning in the list each time , so they will be inverted with the ones in the example...
                    }
                    
                    aux = aux->next;
                }
            }
    }
    
}

void read(char** dest, char* source)
{
    int len = 0;
    len = strlen(source);

    source[strcspn(source, "\n\r")] = '\0';
    *dest = calloc(len + 1, sizeof(char));
    strcpy(*dest, source);
}

void proj()
{
    FILE* fin, * fout;

    fin = fopen("graph.in", "r");
    fout = fopen("graph.out", "w");

    if (fout == NULL || fin == NULL)
    {
        printf("error opening file!\n");
        exit(1);
    }

    int maxi = 0;
    Graph* graf = NULL;
   
    char buffer[1001];
    bool* subgraph_nodes = NULL;

    while (fgets(buffer, 1001, fin)) /// read line by line
    {

        char* data;
        read(&data, buffer); /// read line into a dnamically array of size long as strlen

        if (data[0] == 'V' && data[1] != '`')   /// 1st 2 cases
        {

            char aux[8];
            strncpy(aux, data, 7);
            aux[7] = 0;

            if (strcmp(aux, "V nodes") == 0) ///1st case
            {

                strcpy(data, data + 8);/// in the array we got the nodes values

                data = realloc(data, sizeof(char) * strlen(data) + 1);/// truncate

                if (data == NULL)
                {
                    exit(1);
                }

                char* a = strtok(data, " "); /// tokenization to find max node
                while (a)
                {
                    if (atoi(a) > maxi)
                    {
                        maxi = atoi(a);
                    }
                    a = strtok(NULL, " ");
                }

                init(&graf, maxi);

            }

            else if (strcmp(aux, "V arcs ") == 0) /// 2nd case
            {

                strcpy(data, data + 7);/// in the array we got the nodes values "( )"

                data = realloc(data, sizeof(char) * strlen(data) + 1); /// truncate
                if (data == NULL)
                {
                    exit(2);
                }

                char* aux = data;
                int a, b;

                while (aux < data + strlen(data) + 1)
                {

                    sscanf(aux, "(%d %d)", &a, &b); /// read first couple of "( )" then move to next pair

                    if (graf != NULL)
                    {
                        insert(graf, a, b);
                    }

                    aux++; /// move poiter afer (

                    if (strchr(aux, '(') == NULL) /// no more elements
                    {
                        break;
                    }

                    if (strchr(aux, '(') != NULL) /// points to the array starting with (
                    {
                        aux = strchr(aux, '(');
                    }

                }
            }

        }

        else if (data[0] == 'V' && data[1] == '`') /// last case
        {

            strcpy(data, data + 9);/// in the array we got the nodes values

            data = realloc(data, sizeof(char) * strlen(data) + 1);

            if (data == NULL)
            {
                exit(3);
            }

            subgraph_nodes = calloc(maxi+1, sizeof(bool));

            char* a = strtok(data, " ");
            while (a)
            {
                subgraph_nodes[atoi(a)] = true; /// mark those nodes as part of subgraf
                a = strtok(NULL, " ");
            }

        }

        free(data);
        data = NULL;

    }

    afis(graf, maxi, fout);

    print_arcs_subgraph(graf, subgraph_nodes, maxi,fout);
    
    dealloc(graf, maxi);
    free(graf);
    graf = NULL;
    free(subgraph_nodes);
    
    fclose(fin);
    fclose(fout);
}
