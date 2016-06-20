#include "hash_table.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

/*
 *	FIXME - use dynamic array
 */
static const uint32_t FIXED_ARRAY_SIZE = 256;

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

	return hashval % FIXED_ARRAY_SIZE;
}


hash_table_t* hash_table_constructor() {
	hash_table_t* t = (hash_table_t*)malloc(sizeof(hash_table_t));
	if(t == NULL)
		return NULL;

	t->hash_function = hash_function;
	t->capacity = FIXED_ARRAY_SIZE;
	t->size = 0;
	t->table = (hash_table_entry_t**)malloc(sizeof(hash_table_entry_t*) * t->capacity);

	for(uint32_t i = 0; i < t->capacity; i++) {
		t->table[i] = NULL;
	}

	return t;
}

void hash_table_destructor(hash_table_t* t) {
	if(t == NULL)
		return;

	for(uint32_t i = 0; i < t->capacity; i++) {
		free(t->table[i]);
	}

	free(t->table);
	free(t);
}

int hash_table_insert_elem(hash_table_t* t, const char* key, const char* value) {
	uint32_t hashed_key = t->hash_function(key, strlen(key));

	hash_table_entry_t** entry = &(t->table[hashed_key]);

	while(*entry != NULL ) {
		if(strcmp((*entry)->key, key) == 0) { // Item already inserted
			return 0;
		}
	}
	
	(*entry) = (hash_table_entry_t*)malloc(sizeof(hash_table_entry_t));
	(*entry)->key = strdup(key);
	(*entry)->value = strdup(value);
	t->size++;
	return 1;
}

char* hash_table_find_elem(hash_table_t* t, const char* key) {
	if(t == NULL)
		return NULL;

	uint32_t uikey = t->hash_function(key, strlen(key));
	hash_table_entry_t* entry = t->table[uikey];
	while(entry != NULL && strcmp(entry->key, key) != 0) {
		entry = entry->next;
	}

	if(entry == NULL)
		return NULL;

	return entry->key;
}

int hash_table_update_elem(hash_table_t* t, const char* key, const char* new_value) {
	uint32_t hashed_key = t->hash_function(key, strlen(key));

	hash_table_entry_t** entry = &(t->table[hashed_key]);

	while(*entry != NULL ) {
		if(strcmp((*entry)->key, key) == 0) { // Item already inserted, update it
			free((*entry)->value);
			(*entry)->value = strdup(new_value);
			return 1;
		}
	}

	return 0;
}


void hash_table_delete_elem(hash_table_t* t, const char* key) {
	if(t == NULL)
		return;

	uint32_t uikey = t->hash_function(key, strlen(key));
	hash_table_entry_t** entry = &(t->table[uikey]);
	while(entry != NULL && strcmp((*entry)->key, key) != 0) {
		entry = &(*entry)->next;
	}

	if(*entry == NULL)
		return;

	free((*entry)->key);
	free((*entry)->value);
	free(*entry);

	*entry = (*entry)->next;
	t->size--;
}

long hash_table_size(hash_table_t* t) {
	return t->size;
}

void hash_table_print(hash_table_t* t) {
	if(t == NULL)
		return;

	for(uint32_t i = 0; i < t->size; i++) {
		printf("(%s, %s)\n", t->table[i]->key, t->table[i]->value);
		while(t->table[i]->next) {
			printf("(%s, %s)\n", t->table[i]->next->key, t->table[i]->next->value);
		}
	}
}
