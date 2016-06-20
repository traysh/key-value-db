#ifndef HASH_TABLE_BST_H
#define HASH_TABLE_BST_H

#include "binary_search_tree.h"

/*
 * Simple implementation of a hash_table that stores only C string values
 */
typedef bst_t hash_table_impl;
typedef unsigned int uint32_t;

typedef struct hash_table_bst_t {
	hash_table_impl* impl;
  uint32_t (*hash_function)(const char* key, int len);
} hash_table_bst_t;

/*
 *	To treat collisions, the hash table key must contain both the raw key and the hashed key
 */
typedef struct hash_table_key_t {
	uint32_t* hashed_key;
	char* raw_key;
} hash_table_key_t;

/*
 *	hash_table_bst_t constructor
 */
hash_table_bst_t* hash_table_bst_constructor();

/*
 *	hash_table_bst_t destructor
 */
void hash_table_bst_destructor(hash_table_bst_t* t);

/*
 *	Insert key value pair on hash_map
 *		Return 0 if key was not inserted and 1 otherwise
 */
int hash_table_insert_elem(hash_table_bst_t* t, const char* key, const char* value);

/*
 *	Find info associated with the given key
 *		Return NULL if key is not present
 */
char* hash_table_find_elem(hash_table_bst_t* t, const char* key);

/*
 *	Updates the given key with the new_value
 *		return 0 if something went wrong and 1 otherwise
 */
int hash_table_update_elem(hash_table_bst_t* t, const char* key, const char* new_value);

/*
 *	Deletes the node with the given key
 */
void hash_table_delete_elem(hash_table_bst_t* t, const char* key);

/*
 *	Returns the number of nodes in the hash_table
 */
long hash_table_size(hash_table_bst_t* t);

/*
 *	Helper function that prints all elements inside the hash_table
 */
void hash_table_print(hash_table_bst_t* t);

#endif
