#include<stdlib.h>
#include<stdio.h>

#include "binary_search_tree.h"

/*
 *	Public interface
 */
bst_t* bst_constructor(
	int (*f_compare)(const void* lhs, const void* rhs),
	void (*key_destructor)(void* key),
	void (*info_destructor)(void* info),
	void (*print_key)(const void* key),
	void (*print_info)(const void* info)) 
{
	bst_t* t = (bst_t*)malloc(sizeof(bst_t));
	t->f_compare = f_compare;
	t->key_destructor = key_destructor;
	t->info_destructor = info_destructor;
	t->print_key = print_key;
	t->print_info = print_info;
	t->root = NULL;
	t->size = 0;

	return t;
}

static void bst_destructor_aux(bst_t* t, bst_node_t* p) {
	if(p != NULL) {
		bst_destructor_aux(t, p->left);
		bst_destructor_aux(t, p->right);
		t->key_destructor(p->key);
		t->info_destructor(p->info);
		free(p);
	}
}

void bst_destructor(bst_t* t) {
	bst_destructor_aux(t, t->root);
	free(t);
	t = NULL;
}

bst_node_t* bst_find_node(bst_t* t, void* key) {
	bst_node_t* tree_walker= t->root;
	
	if(tree_walker == NULL)
		return NULL;

	int comparison = t->f_compare(tree_walker->key, key);

	while(comparison != 0) {
		if(comparison == 1) {
			tree_walker = tree_walker->left;
		} else {
			tree_walker = tree_walker->right;
		}

		if(tree_walker == NULL)
			return NULL;

		comparison = t->f_compare(tree_walker->key, key);
	}

	return tree_walker;
}

static bst_node_t* bst_insert_node_aux(bst_t* t, bst_node_t** p, void* key, void* info) {
	if(*p == NULL) {
		bst_node_t* new_node = (bst_node_t*)malloc(sizeof(bst_node_t));
		new_node->left = NULL;
		new_node->right = NULL;
		new_node->key = key;
		new_node->info = info;
		*p = new_node;
		t->size++;

		return *p;
	} else {
		int compare = t->f_compare((*p)->key, key);

		if(compare == 0) {
			return NULL;
		} else if(compare == 1) {
			return bst_insert_node_aux(t, &(*p)->left, key, info);	
		} else {
			return bst_insert_node_aux(t, &(*p)->right, key, info);	
		}
	}
}

bst_node_t* bst_insert_node(bst_t* t, void* key, void* info) {
	return bst_insert_node_aux(t, &t->root, key, info);
}

static bst_node_t* min_value(bst_t* t) {
	if(t == NULL || t->root == NULL)
		return NULL;

	bst_node_t* ret = t->root;
	while(ret->left != NULL) {
		ret = ret->left;
	}
	
	return ret;
}

void bst_delete_node(bst_t* t, void* key) {
	//TODO
}

/*
 *	Preorder print
 */
static void bst_print_aux(bst_t* t, bst_node_t* p) {
	if(p != NULL ) {
		bst_print_aux(t, p->left);
		fprintf(stdout, "Printing node: (");
		t->print_key(p->key);
		fprintf(stdout, ", ");
		t->print_info(p->info);
		fprintf(stdout, ")\n\n");
		bst_print_aux(t, p->right);
	}
}

void bst_print(bst_t* t) {
	bst_print_aux(t, t->root);
}
