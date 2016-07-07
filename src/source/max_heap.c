#include "max_heap.h"

#include <string.h>
#include "stdio.h"
#include "math.h"

heap_t* heap_contructor(
		size_t max_size,
		int (*f_compare)(const void* lhs, const void* rhs),
		void (*key_destructor)(void* key),
		void (*info_destructor)(void* info),
		void (*print_key)(const void* key),
		void (*print_info)(const void* info))
{
	heap_t* h = (heap_t*)malloc(sizeof(heap_t));
	h->size = 0;
	h->max_size = max_size;
	h->data = (heap_node_t*)malloc((max_size+1)*sizeof(heap_node_t));
	
	h->f_compare = f_compare;
	h->key_destructor = key_destructor;
	h->info_destructor = info_destructor;
	h->print_key = print_key;
	h->print_info = print_info;
	
	return h;
}

void heap_destructor(heap_t* h) {
	for (size_t i = 0; i < h->size; ++i) {
		h->key_destructor(h->data[i].key);
		h->info_destructor(h->data[i].info);
	}
	free(h->data);
	free(h);
}

int heap_reserve(heap_t* t, size_t size) {
	heap_node_t* new_data = (heap_node_t*)realloc(t->data, size*sizeof(heap_node_t));
	if (new_data == NULL)
		return 0;
	
	t->data = new_data;
	t->max_size = size;
	return 1;
}

int heap_increase_size(heap_t* t) {
	return heap_reserve(t, t->max_size + HEAP_INITIAL_SIZE);
}

static inline size_t parent_i(size_t node_index) {
	if (node_index == 0)
		return 0;
	
	return (node_index -1)/2;
}

static inline size_t child_left_i(heap_t* h, size_t node_index) {
	size_t child_i = 2*node_index +1;
	if (child_i >= h->size)
		return 0;
	
	return child_i;
}

static inline size_t child_right_i(heap_t* h, size_t node_index) {
	size_t child_i = 2*node_index +2;
	if (child_i >= h->size)
		return 0;
	
	return child_i;
}

static inline void swap(heap_node_t* n1, heap_node_t* n2) {
	heap_node_t tmp;
	memcpy (&tmp, n1, sizeof(tmp));
	memcpy (n1, n2, sizeof(tmp));
	memcpy (n2, &tmp, sizeof(tmp));
}

long heap_insert_node(heap_t* h, void* key, void* info) {
	if (h == NULL)
		return -1;
	
	heap_node_t* data = h->data;
	
	if (h->size == 0) {
		data[0].key = key;
		data[0].info = info;
		++(h->size);
		return 0;
	}
	
	size_t i;
	for (i = (h->size)++; i != 0 && h->f_compare(data[parent_i(i)].key, key) < 0; i = parent_i(i))
		memcpy(&data[i], &data[parent_i(i)], sizeof(heap_node_t));

	data[i].key = key;
	data[i].info = info;
	
	size_t height = log2(h->size);
	size_t first_leaf = pow(2, height);
	
	if (h->size == h->max_size +1) {
		for (size_t i = h->size -1; i >= first_leaf; --i) {
			if (data[i].key < data[h->size -1].key) {
				heap_node_t tmp;
				memcpy(&tmp, &data[h->size-1], sizeof(heap_node_t));
				memcpy(&data[h->size-1], &data[i], sizeof(heap_node_t));
				memcpy(&data[i], &tmp, sizeof(heap_node_t));
			}
		}
		
		h->size = h->max_size;
	}
		
	return (long)i;
}

int heap_delete_node(heap_t* h, size_t index) {
	if (h == NULL || index > h->size-1)
		return 0;
	
	--(h->size);
	if (index == h->size)
		return 1;
	
	heap_node_t* data = h->data;
	
	memcpy(&data[index], &data[h->size], sizeof(heap_node_t));
	
	size_t i = index;
	size_t left_i = child_left_i(h, i);
	size_t right_i = child_right_i(h, i);
	while (left_i || right_i) {
		size_t child_i;
		if (left_i && right_i)
			child_i = h->f_compare(data[left_i].key, data[right_i].key) == 1 ? left_i : right_i;
		else if (left_i)
			child_i = left_i;
		else
			child_i = right_i;
		
		if (h->f_compare(data[child_i].key, data[i].key) < 0)
			break;
		
		swap(&data[i], &data[child_i]);
		i = child_i;
		left_i = child_left_i(h, i);
		right_i = child_right_i(h, i);
	}
	
	if (i != index)
		return 1;
	
	for (; i != 0 && h->f_compare(data[parent_i(i)].key, data[h->size].key) < 0; i = parent_i(i))
		memcpy(&data[i], &data[parent_i(i)], sizeof(heap_node_t));
	
	data[i].key = data[h->size].key;
	data[i].info = data[h->size].info;
	
	return 1;
}

list_t* heap_top_n(heap_t* h) {
	list_t* l = list_constructor(h->key_destructor, h->print_key);
	
	heap_t* t = (heap_t*)malloc(sizeof(heap_t));
	memcpy(t, h, sizeof(heap_t));
	t->data = (heap_node_t*)malloc(t->max_size*sizeof(heap_node_t));
	memcpy(t->data, h->data, t->max_size*sizeof(heap_node_t));
	
	size_t size = (t->max_size < t->size ? t->max_size : t->size);
	for (size_t i = 0; i < size; ++i) {
		list_push_back(l, t->data[0].key);
		heap_delete_node(t, 0);
	}
	
	heap_destructor(t);
	return l;
}

void heap_print(heap_t* h) {
	for (size_t i = 0; i < h->size; ++i) {
		h->print_key(h->data[i].key);
	}
	printf("\n");
}