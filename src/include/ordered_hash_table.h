#ifndef ORDERED_HASH_TABLE_H
#define ORDERED_HASH_TABLE_H

#include "binary_search_tree.h"
#include "max_heap.h"

#include <stdlib.h>

typedef unsigned int uint32_t;

typedef struct ordered_hash_table_entry_t {
	char* key;
	int value;
	size_t heap_index;
	ordered_hash_table_entry_t* next;
} ordered_hash_table_entry_t;

typedef struct ordered_hash_table_t {
	uint32_t size;	// Number of entries inserted
	uint32_t capacity; // size of the underlaying array
	heap_t* ordered_data; // Tree containing ordered data pointers
  uint32_t (*hash_function)(ordered_hash_table_t* t, const char* key, int len);

	ordered_hash_table_entry_t** table;
} ordered_hash_table_t;

typedef struct ordered_hash_table_entry_list_t {
	ordered_hash_table_entry_t* entry;
	ordered_hash_table_entry_list_t* next;
} ordered_hash_table_entry_list_t;

/*
 *	ordered_hash_table_t constructor
 */
ordered_hash_table_t* ordered_hash_table_constructor();
ordered_hash_table_t* ordered_hash_table_constructor(uint32_t capacity);

/*
 *	ordered_hash_table_t destructor
 */
void ordered_hash_table_destructor(ordered_hash_table_t* t);

/*
 *	Insert key value pair on hash_map
 *		Return 0 if key was not inserted and 1 otherwise
 */
int ordered_hash_table_insert_elem(ordered_hash_table_t** t, const char* key, const int value);

/*
 *	Find info associated with the given key
 *		Return NULL if key is not present
 */
ordered_hash_table_entry_t* ordered_hash_table_find_elem(ordered_hash_table_t* t, const char* key);

/*
 *	Returns N entries which contains the ordered top N values
 */
ordered_hash_table_entry_t* ordered_hash_table_get_top_n_values(ordered_hash_table_t* t, int N);

/*
 *	Destroys a list of entries
 */
void ordered_hash_table_destroy_entry_list(ordered_hash_table_entry_list_t* t);

/*
 *	Updates the given key with the new_value
 *		return 0 if something went wrong and 1 otherwise
 */
int ordered_hash_table_update_elem(ordered_hash_table_t* t, const char* key, const int new_value);

/*
 *	Deletes the node with the given key
 */
void ordered_hash_table_delete_elem(ordered_hash_table_t* t, const char* key);

/*
 *	Returns the number of nodes in the ordered_hash_table
 */
long ordered_hash_table_size(ordered_hash_table_t* t);

/*
 *	Helper function that prints all elements inside the ordered_hash_table
 */
void ordered_hash_table_print(ordered_hash_table_t* t);

/*
 *	Compare function of the internal binary search tree
 */
int ordered_hash_table_compare_data(const void* lhs, const void* rhs);

/*
 *	Dummy key destructor of the internal binary search tree
 */
void ordered_hash_table_key_destructor(void* key);

/*
 *	Dummy info destructor of the internal binary search tree
 */
void ordered_hash_table_info_destructor(void* entry);

/*
 *	Key printer of the internal binary search tree
 */
void ordered_hash_table_print_key(const void* key);

/*
 *	Info printer of the internal binary search tree
 */
void ordered_hash_table_print_info(const void* entry);

#endif
