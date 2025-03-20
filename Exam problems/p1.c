#include "p1.h"

/// 2 7 9 5 1 3 5
void diferenta(int n,int*arr,int*rez) {
	int l = 0;
	int elem=arr[0]; /// set as first
	for (int i = 1; i < n; ++i) {
		if (arr[i - 1] < arr[i])
			{
				l++;
			}
		else {
			l = 0;
			*rez = max(*rez,arr[i - 1] - elem);
			elem = arr[i];
		}
	}
	*rez = max(*rez, arr[n - 1] - elem); // possible the last elem
}


void p1() {

	int n, rez = 0;
	int* arr;
	arr = malloc(20 * sizeof(int));

	scanf("%d", &n);

	for (int i = 0; i < n; ++i)
		scanf("%d", arr + i);

	diferenta(n, arr, &rez);
	printf("%d", rez);
	free(arr);

}

////////////////////////////////////////////////////////////////////////////////////////////////////
//BRACKETS

int minSwaps1(char* s) { /// nr de swapuri (rotiri de paranteze adiacente stanga dreapta sa fie balanced)

	int rez = 0;
	int cnt = 0;
	int n = strlen(s);

	for (int i = 0; i < n; ++i) {
		if (s[i] == '(') {
			++cnt;
		}
		else if (s[i] == ')') {
			--cnt;
			if (cnt < 0) {
				rez += 1; /// creste rez , se poate face o rotire
				cnt = 1; /// reset count
			}
		}
	}

	return rez + (cnt / 2);
}

int minSwaps2(char* s) { /// nr de swapuri (aici efectiv muti un bracket cu altu , si la fiecare swap reduci cu 2 nr de inchise ]]] -> []] "[]" e balanced -> ca si cum nu ar exista)

	int cnt = 0;
	int max_balanced = 0;
	int n = strlen(s);

	for (int i = 0; i < n; ++i) {
		if (s[i] == '(') --cnt; /// aici e invers , daca ( scazi cnt
		else ++cnt;
		max_balanced = max(max_balanced, cnt); /// tiunem minte nr max de ))) 
	}

	return (max_balanced+1) / 2;
}

bool isValid(char* str) {
	int count = 0;
	for (int i = 0; str[i]; i++) {
		if (str[i] == '(')
			count++;
		else if (str[i] == ')')
			count--;
		if (count < 0)
			return false;
	}
	return (count == 0);
}


void paranteze(int n, char* X, int k, int nrd, int nri)
{
	for (int i = '('; i <= ')'; i++)
	{
		if (i == '(' && nrd >= n / 2)
			continue;

		else if (i == ')' && nrd == nri)

			continue;

		if (i == '(')
			nrd++;
		else
			nri++;

		X[k] = i;

		if (k == n)
			printf("%s\n", X + 1);
		else
			paranteze(n, X, k + 1, nrd, nri);

		/// backtrack
		if (i == '(')
			nrd--;
		else
			nri--;

	}
}

void p2() {

	char* X = calloc(20, 1); 
	strcpy(X, "())()(");

	printf("%d\n", isValid(X));
	printf("swaps:%d\n", minSwaps1(X));
	printf("swaps:%d\n", minSwaps2(X));

	free(X);
}
 
///////////////////////////////////////////////////////////////////////////////////////////////
//// Partitions

void printi(int* arr,int st,int dr,int*sum,int*cnt) {
	printf("[ ");

	int s = 0;
	for (int i = st; i < dr; ++i) {
		s += arr[i];
		printf("%d ", arr[i]);
	}
	sum[(*cnt)] = s;
	(*cnt)++;

	printf("] ");
}

void p3() {

	int sum_min = 100000,cnt=0;
	int sum_st[10];
	int sum_dr[10];
	int a[40] = {10,20,30,40};
	int n = 4;
	int k=0;

	for (int i = 0; i < n-1 ;i++) { /// n-1 ca ar merge [ 10 20 30 40 ] [ ]
		printf("[ ");

		int s = 0;
		for (int j = 0; j <= k; ++j) { /// prima jumatate
			
			printf("%d ", a[j]);
			s += a[j];
		}
		sum_st[i] = s;
		printf("] ");
		printi(a, k + 1, n,sum_dr,&cnt); /// a doua jumatate de la indice in colo

		printf("\n");
		k++;
	}

	int maxime[10];
	for (int i = 0; i < n - 1; ++i) {
		maxime[i] = max(sum_dr[i], sum_st[i]);
	}

	for (int i = 0; i < n - 1; ++i)
		sum_min = min(sum_min, maxime[i]); /// minimu din maximele alea

	printf("%d ", sum_min);

}
/////////////////////////////////////////////////////////////// M2
int sum(int arr[], int from, int to)
{
	int total = 0;
	for (int i = from; i <= to; i++) /// suma de la un index la altu
		total += arr[i];
	return total;
}

// for n boards and k partitions
int partition(int arr[], int n, int k)
{
	// base cases
	if (k == 1) // one partition , -> tot arrayu
		return sum(arr, 0, n - 1);
	if (n == 1) // one board
		return arr[0];

	int rez = 1000;

	// find minimum of all possible maximum
	// k-1 partitions to the left of arr[i],
	// with i elements, put k-1 th divider
	// between arr[i-1] & arr[i] to get k-th
	// partition
	for (int i = 1; i <= n; i++)
		rez = min(rez, max(partition(arr, i, k - 1), /// max dintre partition i->k-1 si sum -> i->n-1 iti da maximu dintre partitii
			sum(arr, i, n - 1)));

	return rez; /// tu vrei min din maximuele astea
}

void p4() {
	int arr[] = { 10, 20, 60, 50, 30, 40 };
	int n = sizeof(arr) / sizeof(arr[0]);
	int k = 3;
	printf("%d", partition(arr, n, k));
}