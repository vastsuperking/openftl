#ifndef MATRIX_H
#define MATRIX_H

typedef struct Matrix {
	float *array;
	size_t rows, columns;
} Matrix;

// frees a Matrix allocated on the stack
void m_stack_free(Matrix *m);
// frees a Matrix allocated on the heap
void m_heap_free(Matrix *m);
// initializes a Matrix with values
void m_matrix_init(Matrix *m, size_t rows, size_t columns, float *values);
// initializes a Matrix with the same number
void m_fill_init(Matrix *m, size_t rows, size_t columns, float num);
// initializes an identity Matrix of dimensions size * size
void m_identity_init(Matrix *m, size_t size);
// initializes a Matrix with a 2d affine translation
void m_translation_init(Matrix *m, float tx, float ty);
// initializes a Matrix with a 2d affine rotation
void m_rotation_init(Matrix *m, float rot);
// makes a clone of the src Matrix and puts it into the target Matrix
void m_copy(Matrix *target, const Matrix *src);
// prints the Matrix
void m_print(const Matrix *m);
// returns a scaled version of m
Matrix *m_scale(const Matrix *m, float scalar);
// returns the sum of the two Matrices
Matrix *m_sum(const Matrix *m1, const Matrix *m2);
// returns the difference of the two Matrices
Matrix *m_dif(const Matrix *m1, const Matrix *m2);
// returns the product of the two Matrices
Matrix *m_product(const Matrix *m1, const Matrix *m2);
#endif
