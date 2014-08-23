#ifndef VECTOR_H
#define VECTOR_H

typedef enum {
	DOUBLE = 0,
	FLOAT,
	INT,
	LONG,
	NUM_TYPES,
	INVALID 
} VectorType;

typedef struct {
	int size;
	int capacity;
	VectorType type;
	void *data;
} Vector;

void vector_init(Vector *v, VectorType t);
void vector_clear(Vector *v);
void vector_set_int(Vector *v, int index, int val);
int  vector_get_int(const Vector *v, int index);
char *vector_to_string(const Vector *v);

#endif
