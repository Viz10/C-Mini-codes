#include "reverse_word.h"

static void reversing(char* a, char* b) {
	if (a > b) return;

	char swap;
	for (; a < b; a++, b--) {
		swap = *a;
		*a = *b;
		*b = swap;
	}
}

/// ana are mere
/// 

static void reverse1(char*a) { /// strbrk style

	char* p = a;
	char* delim = " ,;:";
	char* end=NULL;

	while (1) {

		end = strpbrk(p, delim); /// da adresa de inceput la delimitor

		if (end == NULL) { /// cand ajunge la ult cuvant nu mai gaseste delimtator deci trebe manual ajuns la adresa la ult ch si dat reverse 
			char* aux = p;
			while (*(aux+1) != '\0') aux++; /// aux acum e la adresa la ult ch din sir

			reversing(p, aux);
			break;
		}

		end--;
		reversing(p, end);
		p = end + 2;

	}
}


///  ana     are mere

static void reverse2(char*a) { /// 2 whiles style

	char* delim = " ,;:";
	int len = strlen(a);

	char* start, * end;

	int i = 0;
	while (i < len) {
		start = a + i;
		while (i < len && strchr(delim, a[i]) == NULL) { /// loop prin cuvant , i la final e pe delimitor
			i++;
		}
		end = a + i - 1;
		reversing(start, end);
		while (i < len && strchr(delim, a[i]) != NULL) { /// loop prin delimitors , i la final e pe primu ch dintr-un cuvant
			i++;
		}
}
}

void reverse_word() {

	char a[101];

	printf("enter  sir:\n");
	fgets(a, 101, stdin);
	a[(strlen(a) - 1)] = 0;

	//reverse1(a);
	reverse2(a);
	printf("%s", a);
}