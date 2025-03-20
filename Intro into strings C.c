#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



/// strlen(a) nr de ch fara '\0'
///a[strlen(a)]= '\0'                indentare de la 0
///a[strlen(a)-1]= ult character


/////////////////////////////////////////////////////////// FUNCTII CITIRE STRING

void citire1(char **a) /// mai ineficienta dpdv al timpului ,  eficienta cu spatiul
{
    char  ch;
    int cnt = 0;

    while((ch = getc(stdin))!='\n') /// citim cate un caracter din terminal
    {
        (*a)[cnt] = ch;
        cnt++;
        *a=realloc(*a,cnt*sizeof(char));
    }
    (*a)[cnt] = '\0';
}


#define BUFF_SIZE 4096
void citire2(char **a) /// mai eficienta dpdv al timpului
{

    char v[BUFF_SIZE];
    int len=0;

    fgets(v,BUFF_SIZE,stdin);

    len=strlen(v);
    v[strlen(v)-1]='\0';

    *a=calloc(len,sizeof(char));

    strcpy(*a,v);

}
///////////////////////////////////////////////////////////////////////////PROBLEMA 2////////////////////////////////////////////////
void p2()
{

    char *a;
    char *rez;
    int starting_point,lengh;
    a=malloc(1);

    printf("enter the position in the source string and lengh desired to extract: (indexing starts from 0!)\n");
    scanf("%d %d",&starting_point,&lengh);

    char c;
    while(c=getchar(),c!='\n') {}

    printf("enter string\n");
    citire1(&a);

    rez=calloc(strlen(a),sizeof(char));

    strncpy(rez,a+starting_point,lengh);
    rez[strlen(rez)]='\0';
    rez=realloc(rez,strlen(rez)*sizeof(char));


    printf("result:%s",rez);


    free(a);
    free(rez);
}

/*
7 11
anamaria a iesit afara
rez: a a iesit a
*/

////////////////////////////////////////////////////////////////////////////////////PROBLEMA 3//////////////////////////////

void p3()
{

    int position;

    printf("string1:\n");
    char *a;
    citire2(&a);
    printf("string2:\n");
    char *b;
    citire2(&b);

    printf("position where to add string2:\n");
    scanf("%d",&position);

    int la,lb;
    la=strlen(a);
    lb=strlen(b);

    int lrez=la+lb+1;
    char *rez;
    rez=calloc(lrez,sizeof(char)); /// sirul nou

    strncpy(rez,a,position); /// copy tot pana la poz de unde incepe insertu
    strcat(rez,b); //insertu
    strcat(rez,a+position); // copy restu de la index in colo

    printf("%s",rez);

    free(a);
    free(b);
    free(rez);
}
/*
01234567891011
unu doi trei
ALFA BETA
9
*/
////////////////////////////////////////////////////////////////////////////////////PROBLEMA 4////////////////////////////

void p4()
{

    int position,lengh;

    printf("start pos of deleted substring and lengh:\n");
    scanf("%d %d",&position,&lengh);

    char c;
    while(c=getchar(),c!='\n') {}

    char *a=malloc(1);
    printf("string:\n");
    citire1(&a);

    char *aux=calloc(strlen(a),sizeof(char)); /// alocam max size pt rez
    strncpy(aux,a,position); /// copiem tot pana la index
    strcat(aux,a+(lengh+position)); /// copiem restul de dupa continutu la care trebe dat skip

    aux=realloc(aux,strlen(aux)*sizeof(char)); /// truncate extra
    printf("%s",aux);

    free(a);
    free(aux);

}
/*
4 18
MASINA ESTE PE STRADA SI COPILUL DOARME
*/
////////////////////////////////////////////////////////////////////////////////////PROBLEMA 5////////////////////////////

void p5()
{
    int cnt=0;
    char *a,*b;

    printf("string1:\n");
    citire2(&a);

    printf("string2:\n");
    citire2(&b);

    char *p=(strstr(a,b));

    if(p==NULL)
    {
        printf("substring is non-existent in source string!");
    }
    else
    {
        for(char *i=a; i<a+strlen(a); i++) /// loop prin adresele din a
        {
            cnt++;
            if(i==p)
            {
                break;
            }
        }
        printf("beginning position of the substring,indexed from 0!\n"); /// se putea si diferenta de pointeri dintre p si a
        printf("%d\n",cnt-1);
        printf("%s\n",p); /// strstr(a,b);
        printf("%c\n",*p); /// caracterul
        printf("%p\n",p); /// adresa
        printf("%s",strchr(a,'i'));
    }
    free(a);
    free(b);
}
/*
char str[] = "Apples are good for your good health";
char word[] = "good";

char* res = strstr(str, word); // res here points to the start of the word "good" in the string str (you can try printing it)
char* res2 = strstr(res + strlen(word), word); // since res points to the start of the word good, we give to strstr that pointer and skip over the length of the word (using strlen)
*/
////////////////////////////////////////////////////////////////////////////////////PROBLEMA 6////////////////////////////

void display_reverse(char *a) /// inverseaza string
{
    for(int i=0,len=strlen(a)-1; i<len; ++i,--len)
    {
        char aux;
        aux=a[i];
        a[i]=a[len];
        a[len]=aux;
    }
}

int nr_cif(int n)
{
    int k=0;
    while(n)
        n=n/10,k++;

    return k;
}

char *num_to_string(double n)
{

    char *string;

    int integer=0;
    if(n-(int)n==0)
        integer = 1;

    if(integer)
    {
        int nr=n;
        int len=nr_cif(nr)+1; /// number + '\0'
        string=calloc(len,sizeof(char));

        int i=0;
        while(nr)
        {
            string[i]=(nr%10)+'0'; /// conv to ascii
            i++;
            nr/=10;
        }
    }
    else
    {
        int size = snprintf(NULL, 0, "%lf", n);  /// lungimea maxima pt string
        string = calloc((size + 1),sizeof(char));
        sprintf(string,"%lf", n); /// introducem continutul la float in string
    }
    return string; /// rez
}

void p6_num_to_string()
{
    char *a;
    double n,cn;
    printf("enter int or float number:\n");
    scanf("%lf",&n);
    cn=n;

    if(cn-(int)cn==0) /// int
    {
        a=num_to_string(n);
        display_reverse(a);
        printf("int to string:\n");
        printf("%s",a);
    }
    else /// float
    {
        a=num_to_string(n);
        printf("float to string:\n");
        printf("%s",a);
    }
    free(a);
}

double string_to_num(char *string)
{


    double rez=0;

    int integer=1;
    if(strchr(string,'.'))
        integer=0;

    if(integer)
    {

        for(int i=0; i<strlen(string); ++i)
            rez=rez*10+string[i]-'0';

    }
    else
    {
        double fp=0;
        int i=0;
        for(; string[i]!='.'; ++i)    /// partea intreaga
        {
            rez=rez*10+string[i]-'0';
        }

        for(int j=i+1; j<strlen(string); ++j)
        {

            fp=fp*10+string[j]-'0'; /// partea fractionara
        }
        rez=rez+fp/pow(10,strlen(string)-i-1);
    }

    return rez;
}

void p6_string_to_num()
{

    char *string ;

    string=calloc(1,sizeof(char));
    printf("enter string that represents an int or a float:\n");
    citire1(&string);

    printf("\n");

    double rez;
    rez=string_to_num(string);
    double fraction=rez-((long)rez);

    if(fraction==0)
    {
        int rez1=rez;
        printf("integer number is: %d\n",rez1);
    }

    else
        printf("float number is: %lf\n",rez);


    free(string);
}

////////////////////////////////////////////////////////////////////////////////////PROBLEMA 7////////////////////////////


void citire_mat_ch(int n,char ***string,int *max_len)
{

    char buffer[BUFF_SIZE];

    *string=calloc(n,sizeof(char*));

    for(int i=0; i<n; ++i)
    {
        fgets(buffer,BUFF_SIZE,stdin);

        buffer[strlen(buffer)-1]='\0';

        if(strlen(buffer)>*max_len)
            *max_len=strlen(buffer);

        (*string)[i]=calloc(strlen(buffer),sizeof(char));
        strcpy((*string)[i],buffer);
    }
}

void clear(int n,char ***string)
{
    if (*string == NULL)
    {
        return;
    }
    for(int i=0; i<n; ++i)
        free((*string)[i]);

    free(*string);
    *string=NULL;
}

void longest(int n,char **string,int max_len)
{
    int index=0;
    for(int i=0; i<n; ++i)
        if(strlen(string[i])==max_len) index=i;

    printf("%s",string[index]);
}

void biggest(int n,char **string,int max_len)
{

    for(int i=0; i<n-1; ++i)
        for(int j=i+1; j<n; ++j)
            if(strcmp(string[i],string[j])>0)
            {
                char aux[max_len+1];
                strcpy(aux,string[i]);
                strcpy(string[i],string[j]);
                strcpy(string[j],aux);
            }
    printf("%s",string[n-1]);
}

void p7()
{
    int n,max_len=0;
    char**string;

    printf("nr of arrays of strings:\n");
    scanf("%d",&n);

    while(getchar()!='\n') {}

    printf("\narrays of strings:\n");
    citire_mat_ch(n,&string,&max_len);

    printf("\n");
    printf("longest string is:\n");
    longest(n,string,max_len);
    printf("\n\n");
    printf("biggest string as seen as a alphanumerica seq is:\n");
    biggest(n,string,max_len);
    printf("\n");

    for(int i=0;i<n;++i)
        printf("%s\n",string[i]);

    clear(n,&string);
}

/*

5
ana maria
masina este mica si are multe reparatii
zanet mananca inghetata
zana este acolo
mucias gracias

*/

////////////////////////////////////////////////////////////////////////////////////PROBLEMA 8////////////////////////////

#define STRING_FORMAT_P8 "Book_%d ( %s; %s; %d)"

typedef struct book
{

    char author[101];
    char title[101];
    int year;
    int index;

} Book;

void read_struct(Book *v,int n)
{

    for(int i=0; i<n; ++i)
    {
        printf("\nEnter datas of book_%d (dates separated by ENTER)\n\n",i+1);

        printf("Author_%d : ",i+1);
        fgets(v[i].author,101,stdin); /// after call ,'\n' is inside the array
        v[i].author[strlen(v[i].author)-1]='\0';

        printf("Title_%d : ",i+1);
        fgets(v[i].title,101,stdin);
        v[i].title[strlen(v[i].title)-1]='\0';

        printf("Publication-Year_%d : ",i+1);
        scanf("%d",&v[i].year);
        v[i].index=i+1;

        while(getchar()!='\n') {}
    }
}


void sort_names(char mat[][101],int n)
{
    for(int i=0; i<n; ++i)
        for(int j=i+1; j<n; ++j)
            if(strcmp(mat[i],mat[j])>0)
            {
                char aux[101];
                strcpy(aux,mat[i]);
                strcpy(mat[i],mat[j]);
                strcpy(mat[j],aux);
            }
    printf("the names of the authors in alphabetic order:\n\n");
    for(int i=0; i<n; ++i)
        printf("%s\n",mat[i]);
}


void swap_books(Book *x,Book *y)  /// swap 2 variables of type Book by reference
{

    Book aux=*x;
    *x=*y;
    *y=aux;

}

void SortDupaAn(Book *v,int n) /// se putea folosi si qsort...
{

    for(int i=0; i<n; ++i)
        for(int j=i+1; j<n; ++j)
            if(v[i].year > v[j].year)
                swap_books(&v[i],&v[j]);  /// swap the books i,j from the book set v

    printf("the names of the authors and the titles of their books in order of the publication year\n\n");
    for(int i=0; i<n; ++i)
        printf(STRING_FORMAT_P8"\n",v[i].index,v[i].author,v[i].title,v[i].year);

}

void p8()
{
    int n;
    printf("nr of books:");
    scanf("%d",&n);
    while(getchar()!='\n') {}

    if(n<1)
    {
        printf("invalid input!");
        exit(1);
    }

    char names[n][101];
    Book v[n];
    read_struct(v,n);

    if(n==1)
    {
        printf("\nthe names of the authors in alphabetic order:\n");
        printf("%s\n",v[0].author);

        printf("\nthe names of the authors and the titles of their books in order of the publication year\n");
        printf(STRING_FORMAT_P8"\n",v[0].index,v[0].author,v[0].title,v[0].year);
    }
    else if(n>1)
    {

        printf("\n");

        for(int i=0; i<n; ++i)
            strcpy(names[i],v[i].author);
        sort_names(names,n);

        printf("\n");
        SortDupaAn(v,n);
    }



}
////////////////////////////////////////////////////////////////////////////////////PROBLEMA 9////////////////////////////

#define STRING_FORMAT_P9_1 "King_%d ( %s; %d -> %d %s)"
#define STRING_FORMAT_P9_2 "King_%d ( %s; %d years )"
#define STRING_FORMAT_P9_3 "King_%d ( %s; %d year )"
#define STRING_FORMAT_P9_4 "King_%d ( %s; less than a year )"

typedef struct
{

    int start;
    int end;
    char name[20];
    int index;
    char erra[3];
    int rull;

} King;

void read_king(King *a,int n)
{

    for(int i=0; i<n; ++i)
    {
        a[i].index=i+1;
        printf("\nKing_%d rulled in BC or AD ? ",i+1);
        scanf("%s",a[i].erra);
        while(getchar()!='\n') {}

        if(strcmp(a[i].erra,"BC")!=0 && strcmp(a[i].erra,"AD")!=0)
        {
            printf("invalid input!");
            exit(1);
        }
        if(strcmp(a[i].erra,"BC")==0)
        {

            printf("\nEnter name of King_%d and the rulling  interval in years BC (dates separated by ENTER)\n",i+1);

        }
        else if(strcmp(a[i].erra,"AD")==0)
        {

            printf("\nEnter name of King_%d and the rulling interval in years AD (dates separated by ENTER)\n",i+1);
        }

            printf("King_%d Name : ",i+1);
            fgets(a[i].name,20,stdin);
            a[i].name[strlen(a[i].name)-1]='\0';

            printf("Start year of rulling for King_%d : ",i+1);
            scanf("%d",&a[i].start);

            printf("End year of rulling for King_%d :",i+1);
            scanf("%d",&a[i].end);
            printf("\n");

            a[i].rull=a[i].end-a[i].start;
            while(getchar()!='\n') {}

            if(a[i].rull<0)
            {
                printf("incorect years input!");
                exit(1);
            }


    }

}

void afisare(King *a,int n)
{

    printf("\nthe list of kings as they were read:\n");
    for(int i=0; i<n; ++i)
        printf("%s\n",a[i].name);

}


void sort_by_name(const King *a,int n) /// sort by names not the struct itself , but a copy of it
{

    King *aux = malloc(n * sizeof(King));
    memcpy(aux, a, n * sizeof(King)); /// create copy

    for(int i=0; i<n-1; ++i)
        for(int j=i+1; j<n; ++j)
            if(strcmp(aux[i].name,aux[j].name)>0)
            {
                King b=aux[i];
                aux[i]=aux[j];
                aux[j]=b;
            }

    printf("kings in alphabetic order, completed with the number of years they ruled:\n");
    for(int i=0; i<n; ++i)
    {
        if(aux[i].rull>1)
            printf(STRING_FORMAT_P9_2"\n",aux[i].index,aux[i].name,aux[i].rull);
        else if(aux[i].rull==1)
            printf(STRING_FORMAT_P9_3"\n",aux[i].index,aux[i].name,aux[i].rull);
        else if(aux[i].rull==0)
            printf(STRING_FORMAT_P9_4"\n",aux[i].index,aux[i].name);
    }
    free(aux);
}

int swap(const void *a,const void *b)
{

    return ((King *)a)->rull - ((King *)b)->rull;

}

void sort_by_rulling(const King *a,int n) /// sort by rulling not the struct itself , but a copy of it
{

    King *aux = malloc(n * sizeof(King));
    memcpy(aux, a, n * sizeof(King));
    qsort(aux,n,sizeof(King),swap);

    printf("\nkings in the ascending order of their ruling time:\n");
    for(int i=0; i<n; ++i)
    {
        if(aux[i].rull>1)
            printf(STRING_FORMAT_P9_2"\n",aux[i].index,aux[i].name,aux[i].rull);
        else if(aux[i].rull==1)
            printf(STRING_FORMAT_P9_3"\n",aux[i].index,aux[i].name,aux[i].rull);
        else if(aux[i].rull==0)
            printf(STRING_FORMAT_P9_4"\n",aux[i].index,aux[i].name);
    }
    free(aux);
}

void p9()
{

    int n;
    printf("nr of kings:");
    scanf("%d",&n);
    while(getchar()!='\n') {}

    if(n<1)
    {
        printf("invalid input!") ;
        exit(1);
    }

    King a[n];
    read_king(a,n);

    if(n==1)
    {
        printf("\nthe list of kings as they were read:\n");
        printf("%s\n",a[0].name);


        printf("\nkings in alphabetic order, completed with the number of years they ruled:\n");
        if(a[0].rull>1)
            printf(STRING_FORMAT_P9_2"\n",a[0].index,a[0].name,a[0].rull);
        else if(a[0].rull==1)
            printf(STRING_FORMAT_P9_3"\n",a[0].index,a[0].name,a[0].rull);
        else if(a[0].rull==0)
            printf(STRING_FORMAT_P9_4"\n",a[0].index,a[0].name);


        printf("\nkings in the ascending order of their ruling time:\n");
        if(a[0].rull>1)
            printf(STRING_FORMAT_P9_2"\n",a[0].index,a[0].name,a[0].rull);
        else if(a[0].rull==1)
            printf(STRING_FORMAT_P9_3"\n",a[0].index,a[0].name,a[0].rull);
        else if(a[0].rull==0)
            printf(STRING_FORMAT_P9_4"\n",a[0].index,a[0].name);

        printf("\nOriginal datas:\n");
        printf(STRING_FORMAT_P9_1"\n",a[0].index,a[0].name,a[0].start,a[0].end,a[0].erra);

    }

    else if(n>1)
    {
        afisare(a,n);
        printf("\n");
        sort_by_name(a,n);
        printf("\n");
        sort_by_rulling(a,n);
        printf("\nOriginal datas:\n");
        for(int i=0; i<n; ++i)
            printf(STRING_FORMAT_P9_1"\n",a[i].index,a[i].name,a[i].start,a[i].end,a[i].erra);
    }


}
////////////////////////////////////////////////////////////////////////////////////PROBLEMA 10////////////////////////////

void citire(char **a,int *len)
{

    char aux[80];

    fgets(aux,80,stdin);
    aux[strlen(aux)-1]='\0';

    *len=strlen(aux);

    *a=calloc(*len,sizeof(char));
    strcpy(*a,aux);

}

#define MAX_LEN 256

int digit(char ch)
{

    return ch>='0' && ch<='9';

}

int letter(char ch)
{

    return (ch>='a' && ch<='z') || (ch>='A' && ch<='Z');

}

void func(char *a,int len,double *sum) /// suma la int si float din propozitie
{


    char mat[len][MAX_LEN];
    int cnt=0;

    char *p=strtok(a," ");

    while(p)
    {
        strcpy(mat[cnt],p);
        cnt++;
        p=strtok(NULL," ");
    }

    for(int i=0; i<cnt; ++i)
    {
        int ok=1;
        int j=0;

        while(j<strlen(mat[i])) /// luam fiecare rand din matricea de cuvinte
        {
            if(letter(mat[i][j])==1  ||  (digit(mat[i][j])==0 && mat[i][j]!='.')) /// de ex Terminator1000 nu se ia 1000 sau 2.5% nu se ia 2.5
            {
                ok=0;
                break;
            }
            j++;
        }

        if(ok==1 && digit(mat[i][0]) && strchr(mat[i],'.') && strlen(mat[i])<=5) /// float
        {
            double nr1=atof(mat[i]);
            *sum=*sum+nr1;
        }

        else if(ok==1 && digit(mat[i][0]) && !strchr(mat[i],'.') && strlen(mat[i])<=5) /// int
        {
            int nr2=atoi(mat[i]);
            *sum=*sum+nr2;
        }
    }
}

void p10()
{

    char *string;
    int len=0;
    double sum=0;

    citire(&string,&len);
    func(string,len,&sum);

    if((sum-(int)sum)==0)
        printf("%g",sum);
    else
        printf("%lf",sum);

    free(string);
}

/// ana are 13 mere si 7 banane si iphone9 si un 7Up
/// ana are 3 mere si 5 banane 2.16 % sanse sa castige un 7Up si o jucarie Terminator1000

int main()
{
    p7();

    return 0;
}





