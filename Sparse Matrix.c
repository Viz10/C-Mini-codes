#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    int i, j, val;
} Element;

void create(int col, int row, int *cnt, Element **mat)
{
    printf("Write the coordinates (i, j) and value of the mat in the matrix:\n");
    printf("Write -1 to stop\n");

    while (1)
    {
        scanf("%d", &(*mat)[*cnt].i);

        if ((*mat)[*cnt].i == -1)
        {
            printf("Read stopped\n");
            break;
        }
        else
            scanf("%d %d", &(*mat)[*cnt].j, &(*mat)[*cnt].val); /// array de structuri alocat dinamic dupa fiecare citire 

        if ((*mat)[*cnt].i > row || (*mat)[*cnt].j > col)
        {
            printf("Coordinates exceed boundaries!\n");
            exit(1);
        }
        (*cnt)++;
        if (*cnt == col * row)
        {
            printf("Maximum nr of elements reached\n\n");
            break;
        }
        *mat = realloc(*mat, sizeof(Element) * (*cnt + 1)); /// initial sirul in main e de 1 element , il citim pt ptima data aici si dupa cum tot citim marim arraytul 
    }
}

void add(int col1,int row1,int col2,int row2,int cnt1,int cnt2,Element *mat1,Element *mat2)
{

    if((col1 != col2) || (row1!=row2))
    {
        printf("not qeual in length!\n");
        exit(1);
    }

    Element *result;
    result=malloc(sizeof(Element)*cnt1); /// alocare pe heap la cnt1 (cate linii sunt) de elemente , returneaza adresa la primu in result => are acces la sir

    for (int l = 0; l < cnt1; ++l)
    {
        result[l].i = mat1[l].i;
        result[l].j = mat1[l].j; /// result devine prima matrice
        result[l].val = mat1[l].val;
    }

    for (int k = 0; k < cnt2; ++k) /// luam fiecare element din mat 2 
    {
        int found = 0; /// found in result mat

        for (int l = 0; l < cnt1; ++l) /// /// luam fiecare element din mat 1
        {
            if (result[l].i == mat2[k].i && result[l].j == mat2[k].j) /// exista elemente la aceeleasi coordonate in ambele metrici
            {
                found = 1;
                result[l].val = result[l].val + mat2[k].val; /// fa suma
                if(result[l].val==0)
                {
                    /// Remove element from array of elements if its value becomes 0
                    for (int m = l; m < cnt1 - 1; ++m)
                    {
                        result[m] = result[m + 1];
                    }
                    cnt1--;
                }
                break; /// luam urm elem din mat2 si comparam
            }
        }

        if (!found) /// !found in result mat  face 0 + val elem din mat2 => adaugam elem in mat1 cu realloc la arrayul de elem
        {
            result = realloc(result, sizeof(Element) * (cnt1+1));
            result[cnt1].i = mat2[k].i;
            result[cnt1].j = mat2[k].j; /// pt ca rez e indexat de la 0 deci daca are 4 elem are de la 0 la 3 indexu
            result[cnt1].val = mat2[k].val;
            cnt1++;
        }
    }

    printf("\nResult after addition mat2 to mat1:\n");
    for(int l=0; l<cnt1; ++l)
        printf("(%d,%d) %d\n",result[l].i,result[l].j,result[l].val);
    free(result);
}

void sub(int col1,int row1,int col2,int row2,int cnt1,int cnt2,Element *mat1,Element *mat2)
{

    if((col1 != col2) || (row1!=row2))
    {
        printf("not qeual in length!\n");
        exit(1);
    }

    Element *result;
    result=malloc(sizeof(Element)*cnt1);

    for (int l = 0; l < cnt1; ++l)
    {
        result[l].i = mat1[l].i;
        result[l].j = mat1[l].j;
        result[l].val = mat1[l].val;
    }

    for (int k = 0; k < cnt2; ++k)
    {
        int found = 0;

        for (int l = 0; l < cnt1; ++l)
        {
            if (result[l].i == mat2[k].i && result[l].j == mat2[k].j)
            {
                found = 1;
                result[l].val = (result[l].val - mat2[k].val);
                if(result[l].val==0)
                {
                    /// Remove element if its value becomes 0
                    for (int m = l; m < cnt1 - 1; ++m)
                    {
                        result[m] = result[m + 1];
                    }
                    cnt1--;
                }
                break;
            }
        }

        if (!found)
        {
            result = realloc(result, sizeof(Element) * (cnt1+1)); /// imi adauga 1 element la final
            result[cnt1].i = mat2[k].i;
            result[cnt1].j = mat2[k].j;
            result[cnt1].val = (mat2[k].val*(-1));
            cnt1++;
        }
    }

    printf("\nResult after subtraction mat2 from mat1:\n");
    for(int l=0; l<cnt1; ++l)
        printf("(%d,%d) %d\n",result[l].i,result[l].j,result[l].val);
    free(result);
}

void multiply(int col1, int row1, int col2, int row2, int cnt1, int cnt2, Element *mat1, Element *mat2)
{
    if (col1 != row2)
    {
        printf("Cannot multiply matrices with incompatible dimensions!\n");
        exit(1);
    }

    // Initialize the result matrix
    Element *result = NULL;
    int cnt_result = 0;

    // Multiply matrices
    for (int a = 0; a < cnt1; ++a)
        for (int b = 0; b < cnt2; ++b)
            if (mat1[a].j == mat2[b].i)
            {
                // Calculate the product value
                int product_val = mat1[a].val * mat2[b].val;

                // Check if the result already has an element at the same position
                int found = 0;
                for (int k = 0; k < cnt_result; ++k)
                {
                    if (result[k].i == mat1[a].i && result[k].j == mat2[b].j)
                    {
                        result[k].val += product_val;
                        found = 1;
                        break;
                    }
                }

                // If no matching element is found, add the product to the result
                if (!found)
                {
                    result = realloc(result, sizeof(Element) * (cnt_result + 1));
                    result[cnt_result].i = mat1[a].i;
                    result[cnt_result].j = mat2[b].j;
                    result[cnt_result].val = product_val;
                    cnt_result++;
                }
            }

    // Print the result
    printf("\nResult after multiplying mat1 with mat2:\n");
    for (int l = 0; l < cnt_result; ++l)
        printf("(%d,%d) %d\n", result[l].i, result[l].j, result[l].val);

    // Free memory
    free(result);
}

void p11()
{
    Element *mat1,*mat2;

    int col1, row1;
    int col2, row2;

    int cnt1=0;
    int cnt2=0;

    printf("Number of rows1 and columns1:\n");
    scanf("%d %d", &row1, &col1);
    mat1=malloc(sizeof(Element));
    create(col1,row1,&cnt1,&mat1);


    printf("\nNumber of rows2 and columns2:\n");
    scanf("%d %d", &row2, &col2);
    mat2=malloc(sizeof(Element));
    create(col2,row2,&cnt2,&mat2);

    printf("\n");

    for(int l=0; l<cnt1; ++l)
    {
        printf("(%d,%d) %d\n",mat1[l].i,mat1[l].j,mat1[l].val);
    }

    printf("\n");

    for(int l=0; l<cnt2; ++l)
    {
        printf("(%d,%d) %d\n",mat2[l].i,mat2[l].j,mat2[l].val);
    }

    //add(col1,row1,col2,row2,cnt1,cnt2,mat1,mat2);
    //sub(col1,row1,col2,row2,cnt1,cnt2,mat1,mat2);
    multiply(col1,row1,col2,row2,cnt1,cnt2,mat1,mat2);

    free(mat1);
    free(mat2);


}

/*
1 1 1
1 2 2
2 1 3
2 2 4

1 2 5
2 1 9
2 2 2
*/
int main()
{

    p11();
    return 0;
}
