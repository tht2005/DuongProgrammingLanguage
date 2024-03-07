/*
 * 	It's similar to std::vector in C++
 * 	Provided functions: empty(), back(), push_back(), pop_back(), at() (random access)
 *
 * 	Example:
 *
 *	// Global
 *	define_vector(int)
 *
 *
 *	int main() {
 *		vector(int) a; // declaration
 *		push_back(&a, 1);
 *		pop_back(&a);
 *		empty(&a);
 *		back(&a);
 *		at(&a, 0);
 *	}
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <assert.h>
#include <stdbool.h>

#include "debug.h"

#define define_vector(type) \
\
	typedef struct { \
		size_t size; \
		type *arr; \
	} _vector_##type; \
\
	bool empty(_vector_##type *v) { \
		return (v->size) == 0; \
	} \
\
	type back(_vector_##type *v) { \
		assert(!empty(v)); \
		return v->arr[v->size - 1]; \
	} \
\
	void push_back(_vector_##type *v, type val) { \
		int new_size = (v->size) + 1; \
		if((new_size & (new_size - 1)) == 0) { \
			v->arr = CP(	realloc(v->arr, 2 * new_size * sizeof(type)), \
					"Out of memory"); \
		} \
		v->arr[v->size] = val; \
		++(v->size); \
	} \
\
	void pop_back(_vector_##type *v) { \
		assert(!empty(v)); \
		--(v->size); \
	} \
\
	size_t size(_vector_##type *v) { \
		return (v->size); \
	} \
\
	type* at(_vector_##type *v, size_t i) { \
		assert(i < (v->size)); \
		return &v->arr[i]; \
	} \
\
	void del(_vector_##type *v) { \
		free(v->arr); \
	}

#define vector(type)	_vector_##type	
#define VECT_INIT	{ 0, NULL }

#endif

