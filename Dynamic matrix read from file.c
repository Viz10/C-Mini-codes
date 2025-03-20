#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{

    FILE *file=fopen("data.in","r");
    if(file==NULL)
    {
        printf("error opening file");
        fclose(file);
        return 1;
    }


    int val;
    char ch;

    int **mat=NULL,vec[101];
    int col=-1,row=-1;

    while(!feof(file))
    {
        while(fscanf(file,"%d%c",&val,&ch)>0) /// aici nu citim tot randul citim cate 2 ch si cand c e \n trecem la linie noua
        {
            if(row==-1)
            {
                row++;
                mat=malloc(sizeof(int*)); /// alocam pt ptima data linie
            }
            
                col++;
                if(col==0)
                {
                    mat[row]=malloc(sizeof(int)*(col+1)); /// prima coloana din linie , array 
                    mat[row][col]=val;
                }
                else
                {
                    mat[row]=realloc(mat[row],sizeof(int)*(col+1)); /// marire pt adauga elemente
                    mat[row][col]=val;
                }

		if(ch=='\n') /// realloc pt a adauga linie noua , ptr nou in arr
            	{
                vec[row]=col;
                row++; /// crestem nr de linii pt urm citire de dupa \n , resetam col 
                col=-1;
                mat=realloc(mat,sizeof(int*)*(row+1));
                break;
           	 }
        }
    }

    mat=realloc(mat,sizeof(int*)*(row));

    for(int i=0; i<row; ++i,printf("\n"))
        for(int j=0; j<=vec[i]; ++j)
        {
            printf("%d ",mat[i][j]);
        }

    for(int i=0; i<row; ++i)
        free(mat[i]);
    free(mat);
    fclose(file);
    return 0;
}
