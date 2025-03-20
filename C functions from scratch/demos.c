#include "myfunc.h"

void func1() {
	FILE* fin = fopen("input.txt", "r");
	if (fin == NULL) {
		printf("%d", errno);
		perror("cannot be opened");
	}

	char* line = NULL;
	char* part = NULL;
	char* aux = NULL;

	size_t lenght = 0;
	size_t read_lenght = 0;

	//char a = '\0';
	//printf("%c\n", a);

	//read_lenght = getdelim(&line, &lenght,'\n', fin);
	//line[read_lenght - 1] = 0;
	//printf("ch read: %zu,buffer size: %zu,line:%s\n", read_lenght, lenght, line);

	//char* freeer = line;
	//while ((part=strsep(&line," ")) != NULL) {
	//	printf("%s\n", part);
	//}

	while ((read_lenght = getline(&line, &lenght, fin)) != -1) {

		line[read_lenght - 1] = 0;
		sort_string(line, read_lenght);
		printf("ch read: %zu,buffer size: %zu,line:%s\n", read_lenght, lenght, line);

		/*
		aux = line;
		while ((part = strsep(&line, " ")) != NULL) {
			printf("%s\n", part);
		} 
		free(aux);
		/// dupa fiecare tokenizare line devine null deci cand citeste din nou , declara getline un nou line ,
		/// insa vechiul line inca e in memorie separat de 0 deci trebe dat free cu aux
		*/
	}

	free(line); /// getline aloca un sir nou , ca line e null dupa ult parsare , insa nu citeste nmc
	fclose(fin);
}
void func2() {
	const char* str = "  12345,6789";
	char* endptr;
	long int num;

	num = strtol(str, &endptr, 10);

	if (endptr == str) {
		printf("No digits were found.\n");
	}
	else {
		printf("The number is: %ld\n", num);
		printf("Remaining string: %s\n", endptr);
	}
	/// str=12345, 67890, 23456  
	/// num=12345
	/// *endptr=',' daca era numa 12345 era '\0' 
	/// daca nu era niciun nr era = str
	
	/*
	const char *str = " 12345, 67890, 23456  ";
    char *endptr=str;
    long int num;

    while (*endptr!='\0') {
        num = strtol(str, &endptr, 10);

        if (str == endptr) {
            break; // No more numbers to process
        }

        printf("The number is: %ld\n", num);
        str = endptr; cut string

        // Skip any commas or spaces
        while (*str == ',' || *str == ' ') {
            str++;
        }
    }
	*/
}
void func3() {	

	enum foo{
		foo_1 = 0,
		foo_2,
		foo_3
	};

	 char my_map[] = {
		[0]='Z',
		[foo_2]='X',
		['a'] = 'A',
		['b'] = 'B',
	};

	for (int i = 0; i < sizeof(my_map) / sizeof(my_map[0]); ++i)
		printf("%c ", my_map[i]);
}
void func4() {
	int a = 1, b = 2;
	MY_FUNC(a, b,int);
}
void func5() {
	int a = 7;
	char* p = (char*)&a;
	for (int i = 0; i < 4; ++i)
		printf("%x ", p[i]);

	printf("\n\n");

	int x[] = {1,2,3,4,5,6,7,8,9,10};

	char* y = (char*)x;
	for (int i = 0; i < sizeof(x); ++i)
		printf("%x ", y[i]);
}
void func6() {

	int a[] = { 9,2,4,5 };
	int c[] = { 1,2,4,5 };
	int b[4];

	//myMemcpy(b, a, 16);
	//for (int i = 0; i < 4; ++i)
		//printf("%d ", b[i]);

	//printf("%d", myMemcmp(a, c, 16));

	char word[100] = "bna are mere ";
	char word2[] = "are";
	char new_word[100];
	
	//printf("%d", myStrlen(word));

	//char str[] = "memmove can be very useful......";
	//myMemmove(str + 20, str + 15, 11);
	//printf("%s",str);
	
	//char*p=myStrcat(word, word2);
	//printf("%s", p);
	
	//char* aa = myStrstr(word, word2);
	//printf("%s", aa);
	
	//int nr = myAtoi("      -0921wfeswgesge88");
	//printf("%d", nr);
	
	//printf("%d\n",myMemcmp(word,word2,6));

	//myMemcpy(new_word, word, sizeof(word));
	

	//myMemset(a, 0,16);

	//for (int i = 0; i < 4; ++i)
	//printf("%d", a[i]);

	//char str[] = "almost every programmer should know memset!";
	//myMemset(str, '-', 6);
	//printf("%s", str);

	int i;
	char strtext[] = "12290s";
	char cset[] = "1234567890";

	i = myStrspn(strtext, cset);
	printf("The initial number has %d digits.\n", i);

}