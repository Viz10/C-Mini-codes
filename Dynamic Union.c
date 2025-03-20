#include <stdio.h>
#include <stdlib.h>

void citire(int n,int *p)
{

    for(int i=0; i<n; ++i)
        scanf("%d",&p[i]);

}

int size=2;
int cnt=0;
void func(int n, int m,int*a, int *b, int **c)
{

    int i=0,j=0;

    while(i<n && j<m)
    {
        if(cnt==size){
            size+=1;
            *c=realloc(*c,sizeof(int)*size);
        }
        if(a[i] < b[j])
        {
            (*c)[cnt] = a[i++];
            cnt++;
        }
        else if(a[i] > b[j])
        {
            (*c)[cnt] = b[j++];
            cnt++;
        }
        else
            i++;
    }

    while(i<n){
        if(cnt==size){
            size+=1;
            *c=realloc(*c,sizeof(int)*size);
        }
        (*c)[cnt] = a[i++];
        cnt++;

    }

    while(j<m){
        if(cnt==size){
            size+=1;
            *c=realloc(*c,sizeof(int)*size);
        }
        (*c)[cnt] = b[j++];
        cnt++;
    }

}

void afisare(int n,int *p)
{
    for(int *u=p; u<p+n; u++)
        printf("%d ",*u);
}

void p4()
{
    int n,m;
    int*a,*b,*c;

    scanf("%d",&n);
    a=malloc(n*sizeof(int));
    citire(n,a);

    scanf("%d",&m);
    b=malloc(m*sizeof(int));
    citire(m,b);

    c=calloc(size,sizeof(int));

    func(n,m,a,b,&c);
    afisare(size,c);

    printf("\n");
    printf("%d",size);

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

int main()
{
    p4();
    return 0;
}
