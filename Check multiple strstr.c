#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *a="money.are crazy money-2 after all";
    char *b="money";
    char *p=NULL;

    int ia=strlen(a);
    int ib=strlen(b);
    int cnt=0;

    p=strstr(a,b);
    cnt++;

    if(p==NULL)
    {
        cnt--;
        printf("\n\n%d",cnt);
        exit(1);
    }

    p=p+ib;
    printf("%s\n",p);
    char *aux;
    while(p<a+ia)
    {
        aux=strstr(p,b);
        if(aux!=NULL)
        {

            cnt++;
            p=aux;
            p=p+ib;
            printf("%s\n",p);
        }
        else
        {
            break;
        }
    }
    printf("\n\n%d",cnt);
    return 0;
}
