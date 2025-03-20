#include "myfunc.h"

char* strsep(char** line, char* delim) {
	if (line == NULL || delim == NULL || *line == NULL) {
		return NULL;
	}
	char* p = *line;
	for (char* aux1 = p; aux1 < p + strlen(p); ++aux1) {
		for (char* aux2 = delim; aux2 < delim + strlen(delim); ++aux2)
			if (*aux1 == *aux2) { /// match
				*line = aux1 + 1; /// cut
				*aux1 = '\0'; /// terminate
				return p;
			}
	}
	/// didnt find any token
	*line = NULL;
	return p;
}
size_t getline(char** line, int* size, FILE* file) {

	if (line==NULL || file == NULL  || size == NULL) {
		return -1;
	}
	
	///	initialization
	if (*size == 0) {
		if(*line != NULL) free(*line);
		 *size = 128;
		 *line = malloc(*size);
		 if (*line == NULL) {
			 return -1;
		 }
	}

	if (*line == NULL) {
		*size = 128;
		*line = malloc(*size);
		if (*line == NULL) {
			return -1;
		}
	}

	int ch;
	size_t read_ch = 0;

	while ( (ch = fgetc(file)) != EOF) {

		if (read_ch >= *size) {
			size_t new_size = *size;
			new_size += (new_size /2)+1;
			char* aux = realloc(*line, new_size);
			if (aux == NULL) {
				return -1;
			}
			*size = new_size;
			*line = aux;
		}
		(*line)[read_ch++] = (char)ch;
		
		if ((char)ch == '\n') { /// we stop at either \n or EOF
			break;
		}
	}
	if (ch == EOF && read_ch == 0) /// empty stream
		return -1;

	(*line)[read_ch] = '\0';

	return read_ch;
}
size_t getdelim(char** line, int* size,int delim, FILE* file) {
	if (line == NULL || file == NULL || size == NULL) {
		return -1;
	}

	///	initialization
	if (*size == 0) {
		if (*line != NULL) free(*line);
		*size = 128;
		*line = malloc(*size);
		if (*line == NULL) {
			return -1;
		}
	}

	if (*line == NULL) {
		*size = 128;
		*line = malloc(*size);
		if (*line == NULL) {
			return -1;
		}
	}

	int ch;
	size_t read_ch = 0;

	while ((ch = fgetc(file)) != EOF) {

		if (read_ch >= *size) { /// realloc
			size_t new_size = *size;
			new_size += (new_size / 2) + 1;
			char* aux = realloc(*line, new_size);
			if (aux == NULL) {
				return -1;
			}
			*size = new_size;
			*line = aux;
		}
		(*line)[read_ch++] = (char)ch;

		if (ch==delim) { /// we stop at either delim or EOF
			break;
		}
	}
	if (ch == EOF && read_ch == 0) /// empty stream
		return -1;

	(*line)[read_ch] = '\0';

	return read_ch;
}

void* myMemcpy(void* dest,const void* source, size_t num) {

	if (dest == NULL || source == NULL) return NULL;

	uint8_t*to  = (uint8_t*)dest;
	const uint8_t* from = (uint8_t*)source;

	//or uint8_t*end  = (uint8_t*)dest + num; while(to<end) 

	for (size_t i = 0; i < num;++i) {
		*(to++) = *(from++);
	}

	return dest;
}
void* myMemmove(void* destination, const void* source, size_t num) {

	if (destination == NULL || source == NULL) {
		return NULL;
	}

	uint8_t* dest = (uint8_t*)destination;
	const uint8_t* src = (uint8_t*)source;

	uint8_t* buffer = malloc(num);
	if (buffer == NULL) return NULL;

	/// copy into buffer data to be transfered
	for (size_t i = 0; i < num; ++i)
		buffer[i] = src[i];

	for (size_t i = 0; i < num; ++i)
		dest[i] = buffer[i];


	free(buffer);
	return destination;
}
int myMemcmp(const void* ptr1, const void*ptr2, size_t num) {

	if (ptr1 == NULL || ptr2 == NULL) return -1;

	const uint8_t* first =   (uint8_t*)ptr1; /// uint8_t must be explicitly cast whereas char not in C
	const uint8_t* second=   (uint8_t*)ptr2;

	for (size_t i = 0; i < num; ++i)
	{
		if (*first != *second) {
			if (*first < *second)
				return -1;
			return 1;
		}
		first++, second++;
	}

	return 0;
}
void* myMemset(void* ptr, int value, size_t num) {
	if (ptr == NULL) return NULL;

	uint8_t* to = (uint8_t*)ptr;

	while (num) {
		*(to++) = value;
		num--;
	}
	return ptr;
}
int myAtoi(const char*str) {
	if (str == NULL)
		return -1;
	const char*ptr = str;
	while (*ptr == ' ') ptr++; // skip white spaces if any
	char ch = *ptr;
	if (ch == '+' || ch == '-') { // check 1st ch.
		ptr++;
	}
	int rez = 0;
	while (*ptr >= '0' && *ptr <= '9') {
		rez *= 10;
		rez += (*ptr) - '0';
		ptr++;
	}
	if (ch == '-') rez *= -1;
	return rez;
}
char* myStrcat(char* dest, const char* start) {
	if (dest == NULL || start == NULL)
		return dest;

	char* aux = dest;

	while (*aux != '\0') aux++; /// shift the ptr until \0
	while (*start != '\0') /// append ch from start string
	{
		*(aux++)=*(start++);
	}
	*aux = 0;

	return dest;
}
size_t myStrlen(const char* str) {
	if (str == NULL)
		return -1;
	size_t rez = 0;
	while (*str != '\0') str++, rez++;
	return rez;
}
const char* myStrstr(const char* str1, const char* str2) {
	
	if (str1 == NULL || str2 == NULL) {
		return NULL;
	}
	const char ch = *str2;
	char* aux1=NULL,*aux2 = NULL;

	while (*str1 != '\0') {
		if (*str1 == ch) { /// explore
			aux1 = str1;
			aux2 = str2;
			while (*aux1 != '\0'  && *aux2 != '\0') {
				if (*aux1 != *aux2) break;
				aux1++, aux2++;
			}
			if (*aux2 == '\0')
				return str1;
		}
		str1++;
	}
	return NULL;
}
size_t myStrspn(const char* str1, const char* str2) {

	if (str1 == NULL || str2 == NULL) return -1;

	size_t rez = 0;
	const char* aux;
	while (*str1 != '\0') {
		aux = str2;
		while (*aux != '\0') {
			if (*aux == *str1) {
				rez++;
				break;
			}
		aux++;
		}

		if (*aux == '\0') return rez; /// ch dosnt match any of str2 ch.

		str1++;
	}
	return rez; /// all were matching ch
}

static int comp(const void* a, const void* b) {
	return *(char*)b - *(char*)a;
}
void sort_string(char* string, int lenght) {
	qsort(string, lenght-1, sizeof(char), comp);
}