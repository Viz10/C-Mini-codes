#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*

    v[i]=*(v+i)

    null pointer
    int a = 10;
    void* ptr = &a;
    printf("%d", *((int*)ptr); cast
*/


/////////////////////////////////////////////////////////////////////PROBLEMA 2 /////////////////////////////////////////////////

/// pentru vectori , matrice alocate dinamic , daca trebuie modificata ea in sine alocare,dealocare etc, se transmite prin referinta

void alocare(int row,int col,int ***mat)
{

    *mat=malloc(sizeof(int*)*row);
    for(int i=0; i<row; ++i)
        (*mat)[i]=malloc(sizeof(int)*col);

}

/// cum **mat e transmis prin referinta la functie se fol inca un '*' in fata,
///iar in funct unde normal se folosea doar 'mat' deobicei , se pune '*mat'
void read_matrix(int *row,int *col,int ***mat)
{

    scanf("%d",row);
    scanf("%d",col);

    alocare(*row,*col,mat);

    for(int i=0; i<*row; ++i)
        for(int j=0; j<*col; ++j)
            scanf("%d",&(*mat)[i][j]);
}

void multiply(int **mat1, int row1, int col1, int **mat2, int row2, int col2,int **rez)
{

    int  suma;

    if (col1 != row2)
    {
        printf("Invalid input");
        return;
    }

    for (int i = 0; i < row1; ++i)
        for (int j = 0; j < col2; ++j)
        {
            suma = 0;
            for (int l = 0; l < col1; ++l) /// luam elementele de pe linia din mat1 si coloana din mat2
            {
                suma += mat1[i][l] * mat2[l][j]; /// inmultim fiecare
            }
            rez[i][j]=suma;
        }
}

void display(int row,int col,int **mat)
{

    for(int i=0; i<row; ++i,printf("\n"))
        for(int j=0; j<col; ++j)
            printf("%d ",mat[i][j]);

}

void clear(int row,int ***mat)
{
    for(int i=0; i<row; i++) /// eliberam adresele din mat
    {
        free((*mat)[i]);
    }
    free(*mat); /// eliberam adresa lui mat
*mat=NULL;
}

void p2()
{

    int **mat1,**mat2,**rez;
    int row1,col1;
    int row2,col2;

    read_matrix(&row1,&col1,&mat1); // le si aloca pe mat 1 si 2
    read_matrix(&row2,&col2,&mat2);

    alocare(row1,col2,&rez);
    multiply(mat1,row1,col1,mat2,row2,col2,rez); /// pass by pointer, schimba remotly adresa la ** 
    printf("\n");
    display(row1,col2,rez);

    clear(row1,&mat1);
    clear(row2,&mat2);
    clear(row1,&rez);
}

/*
3 3
1 1 1
1 1 1
1 1 1

3 3
2 2 2
2 2 2
2 2 2
*/
//////////////////////////////////////////////////////////////////////PROBLEMA 3 /////////////////////////////////////////////////

void sort_ascend(int n,double *v) /// v adresa la primu elem
{
    for(int i=0; i<n-1; ++i)
        for(int j=i+1; j<n; ++j)
            if(*(v+i)>*(v+j)) // = v[i] > v[j]
            {
                double aux;
                aux=*(v+i);
                *(v+i)=*(v+j);
                *(v+j)=aux;
            }
}

void sort_descend(int n,double *v)
{
    for(int i=0; i<n-1; ++i)
        for(int j=i+1; j<n; ++j)
            if(*(v+i)<*(v+j))
            {
                double aux;
                aux=*(v+i);
                *(v+i)=*(v+j);
                *(v+j)=aux;
            }
}

void p3()
{

    char * a;
    double *p;
    int n;
    printf("nr of elements in array:\n");
    scanf("%d",&n);

    a=malloc(10);
    p=malloc(sizeof(double)*n);

    printf("elements in array:\n");
    for(double *urm=p; urm<p+n; urm++)
        scanf("%lf",urm); /// nu mai trebuie pus & , urm e adresa

    printf("ascending or descending sort? type the choice\n");
    scanf("%s",a);

    if(strcmp(a,"ascending")==0)
        sort_ascend(n,p);
    else if(strcmp(a,"descending")==0)
        sort_descend(n,p);
    else
    {
        printf("invalid answer\n");
        return ;
    }

    for(double *urm=p; urm<p+n; urm++) /// se putea si normal cu int i=0 ...
        printf("%lf ",*urm); /// p[i]...

    free(p);
    free(a);

}
///////////////////////////////////////////////////// PROBLEMA 4 /////////////////////////////////////////////////


void citire(int n,double *p)
{

    for(int i=0; i<n; ++i)
        scanf("%lf",&p[i]);

}

void afisare(int n,double *p)
{
    for(double *u=p; u<p+n; u++)
        printf("%lf ",*u);
}

void func(int n, int m,double*a, double *b, double *c,int *cnt) /// elementele care apar si in a si in b nu le cosideram
{
    int i=0,j=0;
    while(i<n && j<m)
    {
        if(a[i] < b[j])
        {
            c[++(*cnt)] = a[i++];
        }
        else if(a[i] > b[j])
        {
            c[++(*cnt)] = b[j++];
        }
        ///  only the distinct elements of the two given vectors
        else if(a[i]==b[j])
        {
            i++;
            j++; /// ignore
        }

    }

    while(i<n)
        c[++(*cnt)] = a[i++];

    while(j<m)
        c[++(*cnt)] = b[j++];

}

void p4()
{

    int n,m;
    int cnt=-1;
    double*a,*b,*c;

    scanf("%d",&n);
    a=malloc(sizeof(double)*n);
    citire(n,a);

    scanf("%d",&m);
    b=malloc(sizeof(double)*m);
    citire(m,b);

    c=calloc((n+m),sizeof(double)); /// o declaram de lungimea maxima pe care o poate avea

    func(n,m,a,b,c,&cnt);

    c=realloc(c,sizeof(double)*(cnt+1)); /// ii scurtam lungimea utila

    afisare(cnt+1,c);

    free(a);
    free(b);
    free(c);

}

/*
4
1 2 3 4
4
2 3 4 5
*/

////////////////////////////////////////////////////// PROBLEMA 5 /////////////////////////////////////////////////
#define BUFF_SIZE 1001
void citire_mat_ch(int n,char ***a,int *maxlen)
{

    char buffer[BUFF_SIZE];

    *a=calloc(n,sizeof(char*)); /// change value for pointer in main

    for(int i=0; i<n; ++i)
    {
        fgets(buffer,BUFF_SIZE,stdin);

        buffer[strlen(buffer)-1]='\0';

        if(strlen(buffer)>*maxlen)
            *maxlen=strlen(buffer);

        (*a)[i]=calloc(strlen(buffer),sizeof(char));
        strcpy((*a)[i],buffer);
    }
}

void free_arrays(int n,char ***a)
{
    if (*a == NULL)
    {
        return;
    }
    for(int i=0; i<n; ++i)
        free((*a)[i]);

    free(*a);
    *a=NULL;
}



void order(int n,char **a,int len)
{

    for(int i=0; i<n-1; ++i)
        for(int j=i+1; j<n; ++j)
        {
            if(strcmp(a[i],a[j])>0)
            {
                char aux[len];
                strcpy(aux,a[i]);
                strcpy(a[i],a[j]);
                strcpy(a[j],aux);
            }
        }



    for(int i=0; i<n; ++i)
        printf("%s\n",a[i]);
}

void p5()
{

    int n;
    int maxlen=0;
    char**a;

    printf("nr of strings:\n");
    scanf("%d",&n);

    while(getchar()!='\n') {}

    printf("\narrays of strings:\n");
    citire_mat_ch(n,&a,&maxlen);

    printf("\n");
    printf("ascending sorted strings:\n\n");
    order(n,a,maxlen);
    free_arrays(n,&a);

}
///////////////////////////////////////////// PROBLEMA 8 /////////////////////////////////////////////////

void citire_coef_pol(int n,int *p)
{

    for(int i=0; i<n; ++i)
        scanf("%d",&p[i]);

}

void afis_pol(int lun,int *pol)
{
    for (int i=lun; i>0; --i)
    {
        printf("%d",*(pol+lun-i));
        if (i!=0)
            printf("x^%d ",i-1);
        if (i != 1)
            printf(" + ");
    }
}

int *calc(int n,int m,int *x,int *y)
{
    int*rez;
    rez=calloc((n*m),sizeof(int));

    for (int i=0; i<n; i++)
        for (int j=0; j<m; j++)
            rez[i+j] =rez[i+j]+(x[i]*y[j]);

    return rez;
}


void p8()
{

    int n,m;
    int *pol1,*pol2;
    int *rez;

    printf("first polynomial degree:\n");
    scanf("%d",&n);
    n=n+1;
    pol1=malloc(sizeof(int)*n);

    printf("first polynomial coef (an..a1,a0):\n");
    citire_coef_pol(n,pol1);

    printf("second polynomial degree:\n");
    scanf("%d",&m);
    m=m+1;
    pol2=malloc(sizeof(int)*m);

    printf("second polynomial coef (an..a1,a0):\n");
    citire_coef_pol(m,pol2);

    rez=calc(n,m,pol1,pol2);
    afis_pol(n+m-1,rez);

    free(pol1);
    free(pol2);
    free(rez);

}

/*
1
1 2
1
3 5
(x+2)(3x+5)
*/

////////////////////////////////////////////////////////////////// PROBLEMA 9 /////////////////////////////////////////////////

void aloc(int n,int ***mat)
{

    *mat=malloc(sizeof(int*)*n);
    for(int i=0; i<n; ++i)
        (*mat)[i]=malloc(sizeof(int)*n);


}

void read_(int *n,int ***mat)
{

    scanf("%d",n);

    aloc(*n,mat);
    printf("square matrix and elements:\n");
    for(int i=0; i<*n; ++i)
        for(int j=0; j<*n; ++j)
            scanf("%d",&(*mat)[i][j]);// (*(*mat+i)+j)
}

void n_pow(int power,int n,int **mat)
{
    int **rez;
    int **copy;

    aloc(n,&rez);
    aloc(n,&copy);

    int  suma;

    for(int k=0; k<power; ++k)
    {
        if(k>0)
        {
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    mat[i][j]=rez[i][j];
        }
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
            {
                if(k==0)
                {
                    copy[i][j]=mat[i][j];
                }
                suma = 0;
                for (int l = 0; l < n; ++l)
                {
                    if(k==0)
                        suma += mat[i][l] * mat[i][l];
                    else if(k>0)
                        suma += mat[i][l] * copy[i][l];
                }
                rez[i][j]=suma;
            }
    }
}

void display_mat(int n,int **mat)
{

    for(int i=0; i<n; ++i,printf("\n"))
        for(int j=0; j<n; ++j)
            printf("%d ",mat[i][j]);

}

void clean(int n,int ***mat)
{
    for(int i=0; i<n; i++)
    {
        free((*mat)[i]);
    }
    free(*mat);
}

void p9()
{

    int **mat;
    int n,power;

    printf("power:\n");
    scanf("%d",&power);

    printf("dimension of square matrix:\n");
    read_(&n,&mat);

    n_pow(power,n,mat);
    printf("\n");
    display_mat(n,mat);

    clean(n,&mat);
}

/*
7
3
1 1 1
1 1 1
1 1 1
*/

////////////////////////////////////////////////////// PROBLEMA 10 /////////////////////////////////////////////////

void aloca(int n,int ***mat)
{

    *mat=malloc(sizeof(int*)*n);
    for(int i=0; i<n; ++i)
        (*mat)[i]=malloc(sizeof(int)*n);

}

void read(int *n,int ***mat)
{

    scanf("%d",n);

    aloca(*n,mat);

    for(int i=0; i<*n; ++i)
        for(int j=0; j<*n; ++j)
            scanf("%d",&(*mat)[i][j]);
}

void afis(int n,int **mat)
{

    for(int i=0; i<n; ++i,printf("\n"))
        for(int j=0; j<n; ++j)
            printf("%d ",*(*(mat+i)+j));

}


void prob(int n,int **mat,int**transpusa)
{

    for(int i=0; i<n; ++i)
        for(int j=0; j<n; ++j)
            *(*(transpusa+i)+j)=*(*(mat+j)+i);

}

void sterge(int n,int ***mat)
{
    for(int i=0; i<n; i++)
    {
        free((*mat)[i]);
    }
    free(*mat);
}

void p10()
{
    int n;
    int **mat,**transpusa;

    read(&n,&mat);
    aloca(n,&transpusa);
    prob(n,mat,transpusa);
    printf("\n");
    afis(n,transpusa);

    sterge(n,&mat);
    sterge(n,&transpusa);

}
/*
3
1 1 1
2 2 2
3 3 3
*/


int main()
{
    p10();
    return 0;
}


