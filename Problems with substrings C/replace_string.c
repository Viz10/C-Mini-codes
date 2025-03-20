#include "replace_string.h"

static void citire(char** sir) {

	char buffer[101];
	fgets(buffer, 101, stdin);
	buffer[strlen(buffer) - 1] = 0;
	*sir = strdup(buffer); /// aloca dinamic strlen de buffer bytes si copy continut , return la adresa de inceput 

}

/// strlen - nr de ch fara \0
/// strstr returneaza un char * deci adresa de unde incepe subsirul gasit in sir
/// si primu param la strstr e de unde sa inceapa , adresa , sa incepa sa caute la fel si la strcpy si strchr

static void subsitute_dinamic(char** array, char* substring, char* with) {

	int l1 = strlen(*array), l2 = strlen(substring),
		lnew = strlen(with);

	int dif = lnew - l2,
		len = strlen(*array) + 1;

	

	char* p = *array; /// points to the the array
	char* aux = NULL;
	char* safe = NULL;
	while (1) {

		aux = strstr(p, substring); /// searches the rem portion for subst

		if (!aux) break;

		if (dif > 0) {
			len = len + dif;     
			safe = *array;/// enlarge array with needed space
			char* old_location = *array;
			safe = realloc(safe, len); /// enlarge  
			if (safe == NULL) {
				printf("error realloc");
				free(*array);
				exit(1);
			}
			*array = safe;
			if (old_location != *array) memset(old_location, 0, strlen(old_location));
			aux = strstr(*array, substring);                    /// get back the pointer to start of found string , poate il muta si aux dinainte se strica
			memmove(aux + lnew, aux + l2, strlen(aux) - strlen(substring) + 1);              /// to make space for the bigger string copy the chars after the substring
											///     asta e cat sa copieze            
			memcpy(aux, with, lnew); /// replace
		}
		else { /// smaller then the subst word
			memcpy(aux, with, lnew);
			memmove(aux + lnew, aux + l2, strlen(aux) - strlen(substring) + 1); /// copy the words after subst directly after thr new with , memmove da copy intrun buffer la with
		}
		p = aux + lnew; /// truncate p to find possible new subst , get after the new with added
	}

	if (dif <= 0) {
		char* old_location=*array;
		safe = *array;
		safe = realloc(safe, strlen(safe) + 1); /// in case of smaller with string , must resize the array after 
		if (safe == NULL) {
			printf("error realloc");
			free(*array);
			exit(1);
		}
		*array = safe;
		if (old_location != *array) memset(old_location, 0, strlen(old_location));
	}
}

void inloc_subsir_dinamic() {

	char* sir = NULL;
	char* substring = NULL;
	char* with = NULL;

	printf("enter  sir:\n");
	citire(&sir);

	
    printf("enter substring:\n");
	citire(&substring);

	printf("enter with:\n");
	citire(&with);

	subsitute_dinamic(&sir, substring, with);

	//printf("%s", sir);

	free(sir);
	free(substring);
	free(with);
}

static void subsitute_stack(char* array, char* substring, char* with, int len_array) {
	char* p = array;
	char* aux = NULL;

	int dif = strlen(with) - strlen(substring),cnt=strlen(array)+1;

	while (p < array + strlen(array)) {

		aux = strstr(p, substring);

		if (!aux) break;

		if (dif > 0) { /// with e mai mare
			cnt += dif;

			if (cnt >= len_array) {
				printf("buffer limit exceeded!\n\n");
				return;
			}

			memmove(aux + strlen(with), aux + strlen(substring), strlen(aux) - strlen(substring) + 1);
			memcpy(aux, with, strlen(with));
		}

		else {
			memcpy(aux, with, strlen(with));
			memmove(aux + strlen(with), aux + strlen(substring), strlen(aux) - strlen(substring) + 1);
		}

		p = aux + strlen(with);
	}
}


void inloc_subsir_stack() {
	char sir[101];
	char substring[51];
	char with[51];

	printf("enter  sir:\n");
	fgets(sir, 101, stdin);
	sir[(strlen(sir) - 1)] = 0;

	printf("enter substring:\n");
	fgets(substring, 51, stdin);
	substring[(strlen(substring) - 1)] = 0;

	printf("enter with:\n");
	fgets(with, 51, stdin);
	with[(strlen(with) - 1)] = 0;

	subsitute_stack(sir, substring, with, 101);

	printf("%s", sir);
}

/*
are ana are mere are
are
banane
*/

//ana are muulte mere si muulte banane
///ana are doua mere si doua banene
/// 
/// ana si mere si banane
/// ana contine mere contine banane
/// 