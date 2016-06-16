#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<limits.h>

#include "hash_table.h"

static void hash_table_print_key(const void* key) {
	fprintf(stdout, "%s", ((hash_table_key_t*)key)->raw_key);
}

static int hash_table_compare(const void* lhs, const void* rhs) {
	hash_table_key_t ulhs = *(hash_table_key_t*)lhs;
	hash_table_key_t urhs = *(hash_table_key_t*)rhs;

	if(*ulhs.hashed_key > *urhs.hashed_key) {
		return 1;
	} else if(*ulhs.hashed_key < *urhs.hashed_key) {
		return -1;
	} else {
		return strcmp(ulhs.raw_key, urhs.raw_key);
	}
}

static void hash_table_key_destructor(void* key) {
	hash_table_key_t* orig_key = (hash_table_key_t*)key;
	free(orig_key->hashed_key);
	free(orig_key->raw_key);
	free(orig_key);
}

static void hash_table_info_destructor(void* info) {
	char* orig_info = (char*)info;
	free(orig_info);
}

static void hash_table_print_info(const void* info) {
	fprintf(stdout, "%s", (char*)info);
}

/*
 *	FIXME - find a better hash function...
 */
static uint32_t hash_function(const char* key, int len) {
	uint32_t hashval = 0;
	int i = 0;

	/* Convert our string to an integer */
	while( hashval < UINT_MAX && i < len ) {
		hashval = hashval << 8;
		hashval += key[ i ];
		i++;
	}

	return hashval;
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
	hash_table_key_t* key;
	char* info;
} pair_t;

static uint32_t* make_uint(uint32_t val) {
	uint32_t* ret = (uint32_t*) malloc(sizeof(uint32_t));
	*ret = val;
	return ret;
}

static hash_table_key_t* make_hash_table_key(hash_table_t* t, const char* key) {
	hash_table_key_t* composed_key = (hash_table_key_t*)malloc(sizeof(hash_table_key_t));

	composed_key->raw_key = strdup(key);
	composed_key->hashed_key = make_uint(t->hash_function(key, strlen(key)));
	return composed_key;
}


static pair_t make_pair(hash_table_t* t, const char* key, const char* info) {
	pair_t p;
	p.key = make_hash_table_key(t, key);
	p.info = strdup(info);

	return p;
}

int hash_table_insert_elem(hash_table_t* t, const char* key, const char* info) {
	if(t == NULL)
		return 0;

	pair_t p = make_pair(t, key, info);
	return bst_insert_node(t->impl, p.key, (void*)p.info) == NULL ? 0 : 1;
}

char* hash_table_find_elem(hash_table_t* t, const char* key) {
	if(t == NULL || t->impl == NULL)
		return NULL;

	hash_table_key_t* hkey = make_hash_table_key(t, key);
	bst_node_t* elem = bst_find_node(t->impl, (void*)hkey);
	hash_table_key_destructor(hkey);

	return elem != NULL ? (char*)elem->info : NULL;
}

int hash_table_update_elem(hash_table_t* t, const char* key, const char* new_value) {
	char* infocpy = strdup(new_value);
	hash_table_key_t* hkey = make_hash_table_key(t, key);
	bst_node_t* result = bst_update_node_info(t->impl, (void*)hkey, (void*)infocpy);
	hash_table_key_destructor(hkey);

	if(result)
		return 1;
	return 0;
}

void hash_table_delete_elem(hash_table_t* t, const char* key) {
	if(t == NULL || t->impl == NULL)
		return;

	hash_table_key_t* hkey = make_hash_table_key(t, key);
	bst_delete_node(t->impl, (void*)hkey);
	hash_table_key_destructor(hkey);
}

long hash_table_size(hash_table_t* t) {
	if(t != NULL && t->impl != NULL)
		return t->impl->size;
	return -1;
}

void hash_table_print(hash_table_t* t) {
	bst_print(t->impl);
}

