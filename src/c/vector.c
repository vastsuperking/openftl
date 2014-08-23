#include "vector.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_CAPACITY 0
#define CAPACITY_INC 16

static unsigned int SIZE[NUM_TYPES] = {sizeof(double), sizeof(float), sizeof(int), sizeof(long)};


static void
vector_alloc(Vector *v) {
	if (v->capacity > 0) {
		v->data = realloc(v->data, SIZE[v->type] * v->capacity);
	} else {
		if (v->data != NULL) {
			free(v->data);
			v->data = NULL;
		}
	}
}

void
vector_init(Vector *v, VectorType t) {
	v->size = 0;
	v->capacity = DEFAULT_CAPACITY;
	v->type = t;
	v->data = NULL;
	vector_alloc(v);
}

void
vector_clear(Vector *v) {
	if (v->data != NULL) free(v->data);
	v->size = 0;
	v->capacity = 0;
	v->type = INVALID;
}

void
vector_set_int(Vector *v, int index, int val) {
	assert(v->type == INT);
	if (index >= v->capacity) {
		v->capacity = (index/CAPACITY_INC + 1) * CAPACITY_INC;
		vector_alloc(v);
	}
	if (index >= v->size) {
		v->size = index + 1;
	}
	assert(v->data != NULL);
	*(((int *) v->data) + index) = val; 
}
int
vector_get_int(const Vector *v, int index) {
	int val;

	assert(v != NULL);
	assert(v->type == INT);
	assert(v->data != NULL);
	assert(index < v->size);

	val = *(((int *) v->data) + index);
	return val;
}

static char *
vector_to_string_int(const Vector *v) {
	const char *popen = "[";
	const char *pclose = "]";
	char tmp[128];
	char *buf = malloc(strlen(popen) + 1);

	strcpy(buf, popen);

	assert(v->type == INT);

	for (int i = 0; i < v->size; i++) {
		int l;
		sprintf(tmp, "%d ", vector_get_int(v, i));
		l = strlen(buf) + strlen(tmp);
		buf = realloc(buf, l);
		strcat(buf, tmp);
	}
	buf = realloc(buf, strlen(buf) + strlen(pclose));
	strcat(buf, pclose);
	return (buf);
}

char *
vector_to_string(const Vector *v) {
	switch (v->type) {
	case INT: return (vector_to_string_int(v));
	default: assert(0); 
	}
	return ("INVALID TYPE");
}

