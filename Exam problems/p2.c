#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int val;
    int nrap;

} element;

void eliminare(char*s)
{

    if(*s!='\0')
    {

        if(*s==*(s+1))
        {
            strcpy(s+1,s+2);
            printf("%s\n",s);
            eliminare(s); /// i--
        }
        else
            eliminare(s+1); /// else i++

    }
}

void cuv()
{
    char s[101];
    fgets(s,101,stdin);
    s[strlen(s)-1]='\0';
    eliminare(s);
    printf("%s",s);
}

void swdvsw(){

int n,m;
    FILE *f=fopen("data.in","r");
    fscanf(f,"%d %d",&n,&m);
    if(f==NULL)
    {
        printf("nu bine");
    }
    element **mat=malloc(n*sizeof(element*)); /// matrice dinamica de structuri de elemente , cu val si nr ap
    for(int i=0; i<n; i++)
    {
        mat[i]=malloc(m*sizeof(element));
    }

    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
        {
            fscanf(f,"%d",&mat[i][j].val); /// citesti din fisier numerele si le pui 0 nr ap
            mat[i][j].nrap=0;
        }

    int max=0;
    for(int j=0; j<m; j++) /// luam coloana
        for(int i=0; i<n; i++) /// luam el de pe linie in jos
        {
            element * aux; /// pt fiecare el luam un pointer , 
            aux=&mat[i][j];
            aux->nrap=1;
            if(aux->nrap>max) /// setam max la 1 ca el o aparut o data
            {
                max=aux->nrap;
            }
            for(int v=j+1; v<m; ++v)
                for(int u=0; u<n; ++u)
                    if(aux->val==mat[u][v].val) /// verificam de la coloana urm in colo daca se regaseste aceeasi val 
                    {
                        aux->nrap++; /// mai crestem la el nr de ap
                        if(aux->nrap>max)
                        {
                            max=aux->nrap; /// updatam max la nr de ap la un el din matrice
                        }
                        break; /// trecem la urm coloana , trb exact o data sa apara pe col
                    }

        }

    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            if(mat[i][j].nrap==max) /// afiseaza doar pe cele cu nr max de ap
                printf("%d\n",mat[i][j].val);

    for(int i=0; i<n; i++)
    {
        free(mat[i]);
    }
    free(mat);

}

int main()
{

    return 0;
}


