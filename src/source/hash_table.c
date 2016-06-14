#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash_table.h"

static int hash_table_compare(const void* lhs, const void* rhs) {
	unsigned int ulhs = *(unsigned int*)lhs;
	unsigned int urhs = *(unsigned int*)rhs;

	if(ulhs > urhs) {
		return 1;
	} else if(ulhs == urhs) {
		return 0;
	} else {
		return -1;
	}
}

static void hash_table_key_destructor(void* key) {
	free(key);
}

static void hash_table_info_destructor(void* info) {
	free(info);
}

static void hash_table_print_key(const void* key) {
	fprintf(stdout, "%d", *((const unsigned int*)key));
}

static void hash_table_print_info(const void* info) {
	fprintf(stdout, "%s", (char*)info);
}

static unsigned int hash_function(const void* key) {
	//TODO
	printf("%s\n", (const char*)key);
	return 1;
}


hash_table_t* hash_table_constructor() {
	hash_table_t* instance = (hash_table_t*)malloc(sizeof(hash_table_t));
	instance->impl = bst_constructor(hash_table_compare, hash_table_key_destructor, hash_table_info_destructor, hash_table_print_key, hash_table_print_info);
	instance->hash_function = hash_function;

	return instance;
}

void hash_table_destructor(hash_table_t* t) {
	if(t == NULL)
		return;

	bst_destructor(t->impl);
	free(t);
}

typedef struct pair_t {
	unsigned int* key;
	char* info;
} pair_t;

static pair_t make_pair(unsigned int* key, const char* info) {
	pair_t p;
	p.key = (unsigned int*)malloc(sizeof(unsigned int));
	*(p.key) = *key;
	p.info = strdup(info);

	return p;
}

int hash_table_insert_elem(hash_table_t* t, const char* key, const char* info) {
	if(t == NULL) 
		return 0;

	unsigned int uikey = t->hash_function(key);
	pair_t p = make_pair(&uikey, info);
	return bst_insert_node(t->impl, p.key, (void*)p.info) == NULL ? 0 : 1;
}

char* hash_table_find_elem(hash_table_t* t, const char* key) {
	if(t == NULL || t->impl == NULL)
		return NULL;

	bst_node_t* elem = bst_find_node(t->impl, (void*)key);
	return elem != NULL ? (char*)elem->info : NULL;
}

int hash_table_update_elem(hash_table_t* t, const char* key, const char* new_value) {
	//TODO
	return -1;
}

void hash_table_delete_elem(hash_table_t* t, const char* key) {
	if(t == NULL || t->impl == NULL)
		return;

	bst_delete_node(t->impl, (void*)key);
}

long hash_table_size(hash_table_t* t) {
	if(t != NULL && t->impl != NULL)
		return t->impl->size;
	return -1;
}

