#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef unsigned int uint32_t;

typedef struct hash_table_entry_t {
	char* key;
	char* value;
	hash_table_entry_t* next;
} hash_table_entry_t;

typedef struct hash_table_t {
	uint32_t size;	// Number of entries inserted
	uint32_t capacity; // size of the underlaying array
  uint32_t (*hash_function)(const char* key, int len);

	hash_table_entry_t** table;
} hash_table_t;

/*
 *	hash_table_t constructor
 */
hash_table_t* hash_table_constructor();

/*
 *	hash_table_t destructor
 */
void hash_table_destructor(hash_table_t* t);

/*
 *	Insert key value pair on hash_map
 *		Return 0 if key was not inserted and 1 otherwise
 */
int hash_table_insert_elem(hash_table_t* t, const char* key, const char* value);

/*
 *	Find info associated with the given key
 *		Return NULL if key is not present
 */
char* hash_table_find_elem(hash_table_t* t, const char* key);

/*
 *	Updates the given key with the new_value
 *		return 0 if something went wrong and 1 otherwise
 */
int hash_table_update_elem(hash_table_t* t, const char* key, const char* new_value);

/*
 *	Deletes the node with the given key
 */
void hash_table_delete_elem(hash_table_t* t, const char* key);

/*
 *	Returns the number of nodes in the hash_table
 */
long hash_table_size(hash_table_t* t);

/*
 *	Helper function that prints all elements inside the hash_table
 */
void hash_table_print(hash_table_t* t);


#endif
