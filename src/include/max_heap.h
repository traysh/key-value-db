#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include <stdlib.h>

#define HEAP_INITIAL_SIZE 1024

typedef struct heap_node_t {
	void* key;
	void* info;
} heap_node_t;

typedef struct heap_t {
	// fields
	size_t size;
	size_t reserved_size;
	heap_node_t* data;
	
	// functions
	int (*f_compare)(const void* lhs, const void* rhs);
	void (*key_destructor)(void* key);
	void (*info_destructor)(void* info);
	void (*print_key)(const void* key);
	void (*print_info)(const void* info);
} heap_t;

heap_t* heap_contructor(
		int (*f_compare)(const void* lhs, const void* rhs),
		void (*key_destructor)(void* key),
		void (*info_destructor)(void* info),
		void (*print_key)(const void* key),
		void (*print_info)(const void* info)
	);

void heap_destructor(heap_t* h);

int heap_reserve(heap_t* t, size_t size);

int heap_increase_size(heap_t* t);

long heap_insert_node(heap_t* h, void* key, void* info);

int heap_delete_node(heap_t* h, size_t index);

heap_node_t* heap_top_n(heap_t* h, size_t N);
	
#endif //MAX_HEAP_H
