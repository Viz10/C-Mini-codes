#include "delete_substring.h"

static void deleting(char* sir, char* substring) {
	char* p = sir;
	char* aux = NULL;

	while (p < sir + strlen(sir)) {
		aux = strstr(p, substring);
		if (!aux) break;
		memmove(aux, aux + strlen(substring), strlen(aux) - strlen(substring) + 1);
		p = aux;
	}
}

/// se putea si dinamic , numa ca acolo trebuia un realloc la final cu strlenul nou, truncate mai mic 

///  ana are mere
///  ana  mere

void delete_substring() {

	char sir[101];
	char substring[51];

	printf("enter  sir:\n");
	fgets(sir, 101, stdin);
	sir[(strlen(sir) - 1)] = 0;

	printf("enter substring:\n");
	fgets(substring, 51, stdin);
	substring[(strlen(substring) - 1)] = 0;

	deleting(sir, substring);
	printf("%s", sir);

}