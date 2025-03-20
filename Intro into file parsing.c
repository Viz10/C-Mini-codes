#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

*/
//////////////////////////////PROBLEMA 2

typedef struct
{

    char name[30];
    char unit[10];
    double amount;
    double price_per_unit;
    int code;

} Item;

#define FORMAT_FILE "%d, %s, %s, %lf, %lf\n"

void p2()
{

    FILE*file;

    file=fopen("items.txt","w+");

    if(file==NULL)
    {
        printf("Error code: %d\n",errno);
        perror("Error message");
        fclose(file);
        return ;
    }


    Item *item;
    int i=-1;

    while(1)
    {
        int ok;
        printf("Add new item? (press 1 for yes , 0 for no (stop reading))\n");

        scanf("%d",&ok);
        if(ok==0)
        {
            printf("\nreading exited\n\n");
            break;
        }

        i++;

        if(i==0)
        {
            item=malloc(sizeof(Item)); /// alocare pt prima data
            if(item==NULL)
            {
                printf("error allocating memory");
                exit(1);
            }
        }
        else if(i>0)
        {
            item=realloc(item,sizeof(Item)*(i+1));
            if(item==NULL)
            {
                printf("error reallocating memory");
                exit(1);
            }
        }
        printf("\nItem %d:\n",i+1); /// citim elementele mai intai intr-un struct

        printf("Code:\n");
        scanf("%d",&item[i].code);

        while(getchar()!='\n') {}

        printf("Name:\n");
        fgets(item[i].name,30,stdin);
        item[i].name[strlen(item[i].name)-1]='\0';

        printf("Unit:\n");
        fgets(item[i].unit,10,stdin);
        item[i].unit[strlen(item[i].unit)-1]='\0';

        printf("Amount:\n");
        scanf("%lf",&item[i].amount);

        printf("Price per unit:\n");
        scanf("%lf",&item[i].price_per_unit);

        while(getchar()!='\n') {}
        /// citim elementele din struct intr-o linie din fisier
        fprintf(file,FORMAT_FILE,item[i].code,item[i].name,item[i].unit,item[i].amount,item[i].price_per_unit);

        printf("\n");
    }

    int lun=i+1;
    printf("LIST:\n");

    for(int i=0; i<lun; ++i)
        printf(FORMAT_FILE,item[i].code,item[i].name,item[i].unit,item[i].amount,item[i].price_per_unit);

    printf("\n");

    free(item);
    fclose(file);

}
/////////////////////////////////////////////////////////////////////////PROBLEMA 3

void swap(Item *a,Item *b)
{

    Item c;
    c=*a;
    *a=*b;
    *b=c;

}

#define FORMAT_STRUCT "%d, %[^,], %[^,], %lf, %lf"

void p3()
{
    FILE *file;
    file=fopen("items.txt","r");

    if(file==NULL)
    {
        printf("Error code: %d\n",errno);
        perror("Error message");
        fclose(file);
        return ;
    }

    rewind(file);

    Item *item=malloc(100*sizeof(Item));
    char buffer[256];

    fgets(buffer,256,file);
    int l=0;

    while(!feof(file))     /// se putea si cu strtok
    {
        if(l==100)
        {
            item=realloc(item,100*sizeof(Item));
        }
        sscanf(buffer,FORMAT_STRUCT,&item[l].code,item[l].name,item[l].unit,&item[l].amount,&item[l].price_per_unit);
        fgets(buffer,256,file);
        l++;

    }

    item=realloc(item,l*sizeof(Item));

    for(int i=0; i<l-1; ++i)
        for(int j=i+1; j<l; ++j)
            if(item[i].code>item[j].code)
            {
                swap(&item[i],&item[j]);
            }


    FILE * ordered_file;
    ordered_file=fopen("items_ordered.txt","w");

    if(ordered_file==NULL)
    {
        printf("Error code: %d\n",errno);
        perror("Error message");
        fclose(ordered_file);
        return ;
    }

    for(int i=0; i<l; ++i)
        fprintf(ordered_file,FORMAT_FILE,item[i].code,item[i].name,item[i].unit,item[i].amount,item[i].price_per_unit);


    fclose(file);
    fclose(ordered_file);
}

/////////////////////////////////////////////////////////////////////////PROBLEMA 4

void input_item(FILE*fin)
{

    fin=fopen("items.txt","a");
    if(fin==NULL)
    {
        printf("Error code: %d\n",errno);
        perror("Error message");
        fclose(fin);
        return ;
    }

    int n;
    printf("how many items to add?\n");

    scanf("%d",&n);

    Item * item;
    item=malloc(sizeof(Item)*n);

    for(int i=0; i<n; ++i)
    {
        printf("\nItem %d:\n",i+1);

        printf("Code:\n");
        scanf("%d",&item[i].code);

        while(getchar()!='\n') {}

        printf("Name:\n");
        fgets(item[i].name,30,stdin);
        item[i].name[strlen(item[i].name)-1]='\0';

        printf("Unit:\n");
        fgets(item[i].unit,10,stdin);
        item[i].unit[strlen(item[i].unit)-1]='\0';

        printf("Amount:\n");
        scanf("%lf",&item[i].amount);

        printf("Price per unit:\n");
        scanf("%lf",&item[i].price_per_unit);

        while(getchar()!='\n') {}

        fprintf(fin,FORMAT_FILE,item[i].code,item[i].name,item[i].unit,item[i].amount,item[i].price_per_unit);

    }
    printf("\nvisit the file to see results\n");
    fclose(fin);
}



void output_item_into_file(FILE*fout,FILE*fin)
{

    fin=fopen("items.txt","r");
    if(fin==NULL)
    {
        printf("Error code: %d\n",errno);
        perror("Error message");
        fclose(fin);
        return ;
    }

    fout=fopen("items_output.txt","w");
    if(fout==NULL)
    {
        printf("Error code: %d\n",errno);
        perror("Error message");
        fclose(fout);
        return ;
    }

    int n;
    printf("how many items do you want to output?:\n");
    scanf("%d",&n);

    int ok=0;
    for(int i=0; i<n; ++i)
    {
        rewind(fin);

        int nr;
        printf("enter code of item to output:\n");
        scanf("%d",&nr);

        char buffer[256];

        fgets(buffer,256,fin);
        while (!feof(fin))
        {
            int code;
            sscanf(buffer, "%d", &code);

            if (code == nr)
            {
                ok++;
                fputs(buffer, fout);
                break;
            }
            fgets(buffer,256,fin);
        }
    }


    if(ok==0)
    {
        printf("wrong id inputs");
        exit(1);
    }

    printf("\nvisit the file to see results\n");
    fclose(fout);
    fclose(fin);
}


void p4()
{
    int nr;
    printf("in order to test the input and output functions : select\n1 for input\n2 for output\n\n");
    scanf("%d",&nr);

    while(getchar()!='\n') {}

    FILE*fin=NULL;
    FILE*fout=NULL;

    if(nr==1)
    {
        input_item(fin); /// append elements to the shop
    }
    else if(nr==2)
    {
        output_item_into_file(fout,fin); /// output elements based on their codes in the shop
    }
    else
    {
        printf("wrong input");
    }


}

/////////////////////////////////////////////////////////////////////////PROBLEMA 6


void show_label_row(FILE *file)
{

    char buffer[256];
    file=fopen("text.dat","r");

    if(file==NULL)
    {
        printf("Error code: %d\n",errno);
        perror("Error message");
        fclose(file);
        return ;
    }

    rewind(file);

    int i=1;


    fgets(buffer,256, file);
    while(!feof(file))
    {
        printf("%d) %s",i,buffer);
        fgets(buffer,256, file);
        i++;
    }

    fclose(file);
}

void p6()
{

    FILE *file;
    char buffer[256];

    file = fopen("text.dat", "w");

    if(file==NULL)
    {
        printf("Error code: %d\n",errno);
        perror("Error message");
        fclose(file);
        return ;
    }

    printf("Enter text (Ctrl+Z to end input(Win)\nCtrl+D to end input(Linux,macOS)):\n"); /// signal to stop

    while (fgets(buffer, 256, stdin) != NULL)
    {
        fputs(buffer, file);
    }

    fclose(file);

    FILE*fin=NULL;
    show_label_row(fin);
    fclose(fin);

}


/////////////////////////////////////////////////////////////////////////PROBLEMA 9

void concatenate_files(FILE *fin,int n,char names[][50])
{

    fin=fopen("concatenated.txt","w");

    if(fin==NULL)
    {
        printf("Error code: %d\n",errno);
        perror("Error message");
        fclose(fin);
        return ;
    }


    for(int i=0; i<n; ++i)
    {

        FILE *file;
        file=fopen(names[i],"r");

        if(file==NULL)
        {
            printf("Error code: %d\n",errno);
            perror("Error message");
            fclose(file);
            return ;
        }

        rewind(file);
        char buffer[256];
        fgets(buffer,256, file);

        while(!feof(file))
        {
            fputs(buffer, fin);
            fgets(buffer,256, file);
        }
        fclose(file);
    }


}

void p9()
{
    char names[50][50];
    int n;
    printf("how many files are , containing real numbers?\n");
    scanf("%d",&n);

    while(getchar()!='\n') {}

    for(int i=0; i<n; ++i)
    {
        printf("enter file %d name to write the numbers:\n",i+1);
        fgets(names[i],50,stdin);
        names[i][strlen(names[i])-1]='\0';

        FILE *file;
        file=fopen(names[i],"w");

        if(file==NULL)
        {
            printf("Error code: %d\n",errno);
            perror("Error message");
            fclose(file);
            return ;
        }
        char buffer[256];
        printf("Enter text (Ctrl+Z to end input(Win)/Ctrl+D to end input(Linux,macOS)):\n");

        while(fgets(buffer,256, stdin)!=NULL)
        {
            fputs(buffer, file);
        }
        fflush(stdin);
        fclose(file);
    }

    printf("check files for results\n");
    FILE *fin=NULL;
    concatenate_files(fin,n,names);
    fclose(fin);

}

/////////////////////////////////////////////////////////////////////////////////// PROBLEMA 11

// Structure to represent a car
struct Car {
    char brand[50];
    char owner[50];
    char color[20];
    char number[15];
};

// Function to compare two cars based on owner's name 
int compareCars(const void *a, const void *b) {
    return strcmp(((struct Car *)a)->owner, ((struct Car *)b)->owner);
}

void p11(){


int numCars;
    char filename[50];
    char searchColor[20];

    // Get the number of cars from the user
    printf("Enter the number of cars: ");
    scanf("%d", &numCars);

    // Create an array of structures to store car data
    struct Car cars[numCars];

    // Get car data from the user
    for (int i = 0; i < numCars; i++) {
        printf("\nEnter details for Car %d:\n", i + 1);
        printf("Brand: ");
        scanf("%s", cars[i].brand);
        printf("Owner: ");
        scanf("%s", cars[i].owner);
        printf("Color: ");
        scanf("%s", cars[i].color);
        printf("Number Plate: ");
        scanf("%s", cars[i].number);
    }

    // Get the filename from the user and write car data to the file
    printf("\nEnter the filename to save car data: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for writing.\n");
        return 1;
    }

    // Write car data to the file
    fwrite(cars, sizeof(struct Car), numCars, file); /// BINARY SENT THE CAR STRUCT ADRESS
    fclose(file);

    // Get the color to search for
    printf("\nEnter the color to search for: ");
    scanf("%s", searchColor);

    // Read car data from the file and filter by color
    file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for reading.\n");
        return 1;
    }

    // Read car data from the file
    fread(cars, sizeof(struct Car), numCars, file);
    fclose(file);

    // Filter cars by color
    printf("\nCars with color %s, ordered by owner's name:\n", searchColor);

    // Sort cars by owner's name
    qsort(cars, numCars, sizeof(struct Car), compareCars);

    // Display cars with the specified color
    for (int i = 0; i < numCars; i++) {
        if (strcmp(cars[i].color, searchColor) == 0) {
            printf("Brand: %s, Owner: %s, Color: %s, Number: %s\n",
                   cars[i].brand, cars[i].owner, cars[i].color, cars[i].number);
        }
    }

}
///////////////////////////////////////////////////////////////////////PROBLEMA 12

#define MAX_LINE_LENGTH 1000

void p12(){

// Open the first file for reading
    FILE *file1 = fopen("file1.txt", "r");
    if (file1 == NULL) {
        perror("Error opening file1.txt");
        exit(EXIT_FAILURE);
    }

    // Open the second file for reading
    FILE *file2 = fopen("file2.txt", "r");
    if (file2 == NULL) {
        perror("Error opening file2.txt");
        fclose(file1);
        exit(EXIT_FAILURE);
    }

    char line1[MAX_LINE_LENGTH], line2[MAX_LINE_LENGTH];
    int lineNumber = 0;

    // Read and compare lines from both files
    while (fgets(line1, MAX_LINE_LENGTH, file1) != NULL &&
           fgets(line2, MAX_LINE_LENGTH, file2) != NULL) {
        lineNumber++;

        // Remove newline characters from the lines using strlen
        if (line1[strlen(line1) - 1] == '\n') {
            line1[strlen(line1) - 1] = '\0';
        }

        if (line2[strlen(line2) - 1] == '\n') {
            line2[strlen(line2) - 1] = '\0';
        }

        // Compare lines and print if different
        if (strcmp(line1, line2) != 0) {
            printf("Difference at line %d:\n", lineNumber);
            printf("File 1: %s\n", line1);
            printf("File 2: %s\n", line2);
            printf("\n");
        }
    }

    // Check for any remaining lines in either file
    while (fgets(line1, MAX_LINE_LENGTH, file1) != NULL) {
        lineNumber++;
        if (line1[strlen(line1) - 1] == '\n') {
            line1[strlen(line1) - 1] = '\0';
        }
        printf("Difference at line %d:\n", lineNumber);
        printf("File 1: %s\n", line1);
        printf("File 2: [End of file]\n");
        printf("\n");
    }

    while (fgets(line2, MAX_LINE_LENGTH, file2) != NULL) {
        lineNumber++;
        if (line2[strlen(line2) - 1] == '\n') {
            line2[strlen(line2) - 1] = '\0';
        }
        printf("Difference at line %d:\n", lineNumber);
        printf("File 1: [End of file]\n");
        printf("File 2: %s\n", line2);
        printf("\n");
    }

    // Close the files
    fclose(file1);
    fclose(file2);

}




/////////////////////////////////////////////////////////////////
int main()
{
    ///1, 2, 3, 4, 6, 9
    //p2();
    //p3();
    //p4();
    //p6();
    //p9();
    //p11();
    //p12();
    return 0;
}
