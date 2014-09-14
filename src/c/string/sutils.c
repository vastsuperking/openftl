#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sutils.h"

char *substring(const char *str, size_t start, size_t end) {
	char *sub;
	if (end > strlen(str) || end <= start) {
		return NULL;
	}
	
	sub = malloc(end - start);
	strncpy(sub, str + start, end - start);
	return sub;
}

char **split(const char *str, const char *delimeters) {
	char **tokens, *token, *strCopy, *null;
	size_t index = 0, bufSize = 10;
	strCopy = malloc(strlen(str));
	strcpy(strCopy, str);
	null = malloc(2);
	strcpy(null, "\0");
	tokens = malloc(bufSize * sizeof(char *));
	token = strtok(strCopy, delimeters);
	while (token != NULL) {
		if (index >= bufSize - 1) {
			bufSize *= 2;
			tokens = realloc(tokens, bufSize * sizeof(char *));
		}
		
		*(tokens + index) = token;
		
		index++;
		token = strtok(NULL, delimeters);
	}
	*(tokens + index) = null;
	return tokens;
}

unsigned int frequency(const char *str, const char *regex) {
	unsigned int frequency;
	size_t stringlen = strlen(str), reglen = strlen(regex);
	for (size_t i = 0; i < stringlen; i++) {
		if (memcmp(str + i, regex, reglen) == 0) {
			frequency++;
		}
	}
	return frequency;
}

char *replace_all(const char *str, const char *regex, const char *replacement) {
	unsigned int freq = frequency(str, regex);
	size_t stringlen = strlen(str), reglen = strlen(regex), replen = strlen(replacement);
	const char *ptr = str, *lastptr = str;
	char *new, *cpyptr;
	new = malloc(stringlen + (replen - reglen) * freq);
	cpyptr = new;
	for (unsigned int i = 0; i < freq; i++) {
		ptr = strstr(ptr, regex);
		memcpy(cpyptr, lastptr, ptr - lastptr);
		cpyptr += ptr - lastptr;
		memcpy(cpyptr, replacement, replen);
		cpyptr += replen;
		ptr += reglen;
		lastptr = ptr;
	}
	return new;
}

int main() {
	printf("%s\n", replace_all("lol free lol lol fdlol", "lol", "hey"));
	return 0;
}
