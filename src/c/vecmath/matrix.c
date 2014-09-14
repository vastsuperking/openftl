#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "matrix.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void m_stack_free(Matrix *m) {
	free(m->array);
}

void m_heap_free(Matrix *m) {
	free(m->array);
	free(m);
}

static float getVal(const Matrix *m, size_t row, size_t column) {
	return *(m->array + row * m->columns + column);
}

static void setVal(Matrix *m, size_t row, size_t column, float val) {
	*(m->array + row * m->columns + column) = val;
}

static void m_init(Matrix *m, size_t rows, size_t columns) {
	float *array;
	if (rows < 1 || columns < 1) {
		perror("Rows and columns must be greater than 0!");
	}
	
	array = malloc(sizeof(float) * rows * columns);
	m->array = array;
	m->rows = rows;
	m->columns = columns;
}

void m_matrix_init(Matrix *m, size_t rows, size_t columns, float *values) {
	size_t len = rows * columns;
	m_init(m, rows, columns);

	for (size_t i = 0; i < len; i++) {
		*(m->array + i) = *(values + i);
	}
}

void m_fill_init(Matrix *m, size_t rows, size_t columns, float num) {
	size_t len = rows * columns;
	m_init(m, rows, columns);
	for (unsigned int i = 0; i < len; i++) {
		*(m->array + i) = num;
	}
}

void m_identity_init(Matrix *m, size_t size) {
	size_t len = size * size;
	m_init(m, size, size);
	for (unsigned int i = 0; i < len; i++) {
		*(m->array + i) = i % (size + 1) == 0 ? 1 : 0;
	}
}

void m_translation_init(Matrix *m, float tx, float ty) {
	float array[] = {1, 0, tx, 0, 1, ty, 0, 0, 1};
	m_init(m, 3, 3);
	memcpy(m->array, array, sizeof(float) * 9);
}

void m_rotation_init(Matrix *m, float rot) {
	float array[] = {-cos(rot), -sin(rot), 0, sin(rot), -cos(rot), 0, 0, 0, 1};
	m_init(m, 3, 3);
	memcpy(m->array, array, sizeof(float) * 9);
}

void m_clone(Matrix *target, const Matrix *src) {
	size_t len = sizeof(float) * src->rows * src->columns;
	float *array = malloc(len);
	memcpy(array, src->array, len);
	target->array = array;
	target->rows = src->rows;
	target->columns = src->columns;
}

void m_print(const Matrix *m) {
	size_t rows = m->rows, columns = m->columns;
	float val;
	for (unsigned int r = 0; r < rows; r++) {
		printf("[");
		for (unsigned int c = 0; c < columns; c++) {
			// why no seg fault if c = columns?
			val = getVal(m, r, c);
			if (c < columns - 1) {
				printf("%f\t", val);
			} else {
				printf("%f", val);
			}
		}
		printf("]\n");
	}
}

Matrix *m_scale(const Matrix *m, float scalar) {
	Matrix *new = malloc(sizeof(Matrix));
	size_t len = m->rows * m->columns;
	m_init(new, m->rows, m->columns);
	
	for (unsigned int i = 0; i < len; i++) {
		*(new->array + i) = *(m->array + i) * scalar;
	}
	
	return new;
}

Matrix *m_sum(const Matrix *m1, const Matrix *m2) {
	Matrix *new = malloc(sizeof(Matrix));
	size_t len = m1->rows * m1->columns;

	if (m1->rows != m2->rows || m1->columns != m2->columns) {
		perror("Sum must be of equal dimensional matrices!");
	}

	m_init(new, m1->rows, m1->columns);
	for (unsigned int i = 0; i < len; i++) {
		*(new->array + i) = *(m1->array + i) + *(m2->array + i);
	}
	
	return new;
}

Matrix *m_dif(const Matrix *m1, const Matrix *m2) {
	Matrix *new = malloc(sizeof(Matrix));
	size_t len = m1->rows * m1->columns;

	if (m1->rows != m2->rows || m1->columns != m2->columns) {
		perror("Sum must be of equal dimensional matrices!");
	}

	m_init(new, m1->rows, m1->columns);
	for (unsigned int i = 0; i < len; i++) {
		*(new->array + i) = *(m1->array + i) - *(m2->array + i);
	}
	
	return new;
}

Matrix *m_product(const Matrix *m1, const Matrix *m2) {
	Matrix *new = malloc(sizeof(Matrix));
	size_t rows = m1->rows, columns = m2->columns;
	float dotProduct;
	
	if (m1->columns != m2->rows) {
		perror("Columns in first must equal rows in second!");
	}

	m_init(new, rows, columns);
	for (size_t r = 0; r < rows; r++) {
		for (size_t c = 0; c < columns; c++) {
			dotProduct = 0;
			for (size_t i = 0; i < m1->columns; i++) {
				dotProduct += getVal(m1, r, i) * getVal(m2, i, c);
			}

			setVal(new, r, c, dotProduct);
		}
	}

	return new;
}
// a demo function
void test() {
	// affine and pos are on stack, product is pointer to Matrix on heap
	Matrix affine, pos, *product;
	float coords[] = {-2, 0, 1};
	
	m_rotation_init(&affine, M_PI / 2);
	m_print(&affine);
	printf("\n");
	m_matrix_init(&pos, 3, 1, coords);
	m_print(&pos);
	printf("\n");
	product = m_product(&affine, &pos);
	m_print(product);
	
	m_stack_free(&affine);
	m_stack_free(&pos);
	m_heap_free(product);
}
