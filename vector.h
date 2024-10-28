#ifndef _VECTOR_HEADER
#define _VECTOR_HEADER

#include <stdlib.h>

#define VEC_IMPL(word) VEC_COMB1(VEC_PREFIX, word)
#define VEC_COMB1(pre, word) VEC_COMB2(pre, word)
#define VEC_COMB2(pre, word) pre##word

#endif // _VECTOR_HEADER

#ifndef VEC_T 
#error "VEC_T must be defined"
#endif // VECTOR_T

#ifndef VEC_NAME 
#define VEC_NAME VEC_COMB1(VEC_COMB1(darray, _), VEC_T)
#endif // VECTOR_NAME

#ifndef VEC_PREFIX
#define VEC_PREFIX VEC_COMB1(VEC_NAME, _)
#endif // VECTOR_PREFIX

#ifndef VEC_LINKAGE
#define VEC_LINKAGE static inline
#endif // VECTOR_LINKAGE

typedef struct VEC_NAME VEC_NAME;
struct VEC_NAME {
	VEC_T* data;
        size_t count;
        size_t capacity;
};

#define VEC_push VEC_IMPL(push)

#ifdef VEC_DECLS_ONLY

VEC_LINKAGE
void 
VEC_push(VEC_NAME* array, VEC_T item);

#else

VEC_LINKAGE
void
VEC_push(VEC_NAME* array, VEC_T item) {
	if (array->count >= array->capacity) {
		size_t old_cap = array->capacity;
		size_t new_cap = old_cap?old_cap*2:4;
                size_t new_size = new_cap * sizeof(VEC_T);
                array->data = realloc(array->data, new_size);
                array->capacity = new_cap;
	}
	array->data[array->count++] = item;
}
#endif

#undef VEC_T
#undef VEC_PREFIX
#undef VEC_NAME
#undef VEC_LIKAGE
#undef VEC_push
#ifdef VEC_DECLS_ONLY
#undef VEC_DECLS_ONLY
#endif


