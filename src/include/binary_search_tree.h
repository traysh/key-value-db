#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

typedef struct bst_node_t {
	void* key;	// index for searching
	void* info; // value stored 

	struct bst_node_t* left;
	struct bst_node_t* right;
} bst_node_t;

typedef struct bst_t {
	/*
	 *	bst_t fields
	 */
	bst_node_t* root;
	long size;

	/*
	 *	bst_t functions
	 */
	int (*f_compare)(const void* lhs, const void* rhs);
	void (*key_destructor)(void* key);
	void (*info_destructor)(void* info);
	void (*print_key)(const void* key);
	void (*print_info)(const void* info);
} bst_t;

/*
 *	bst_t _constructor
 */
bst_t* bst_constructor(
	int (*f_compare)(const void* lhs, const void* rhs),
	void (*key_destructor)(void* key),
	void (*info_destructor)(void* info),
	void (*print_key)(const void* key),
	void (*print_info)(const void* info)
);

/*
 *	bst_t destructor
 */
void bst_destructor(bst_t* t);

/*
 *	Returns a pointer to the node with the given index or 
 *		NULL if the index is not present
 */
bst_node_t* bst_find_node(bst_t* t, void* key);

/*
 *	Returns a pointer to the node inserted or NULL if something went wrong
 */
bst_node_t* bst_insert_node(bst_t* t, void* key, void* info);

/*
 *	Deletes the node with the given key from the tree
 */
void bst_delete_node(bst_t* t, void* key);

/*
 *	Prints the tree using print_key and print_info functions 
 */
void bst_print(bst_t* t);


#endif
