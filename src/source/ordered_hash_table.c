#include "ordered_hash_table.h"
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
static uint32_t hash_function(ordered_hash_table_t* t, const char* key, int len) {
	uint32_t hashval = 0;
	int i = 0;

	/* Convert our string to an integer */
	while( hashval < UINT_MAX && i < len ) {
		hashval = hashval << 8;
		hashval += key[ i ];
		i++;
	}

	return hashval % t->capacity;
}


ordered_hash_table_t* ordered_hash_table_constructor() {
	return ordered_hash_table_constructor(FIXED_ARRAY_SIZE);
}

ordered_hash_table_t* ordered_hash_table_constructor(uint32_t capacity) {
	ordered_hash_table_t* t = (ordered_hash_table_t*)malloc(sizeof(ordered_hash_table_t));
	if(t == NULL)
		return NULL;

	t->hash_function = hash_function;
	t->capacity = capacity;
	t->size = 0;
	t->table = (ordered_hash_table_entry_t**)malloc(sizeof(ordered_hash_table_entry_t*) * t->capacity);
	
	t->ordered_data = heap_contructor(
		ordered_hash_table_compare_data,
		ordered_hash_table_key_destructor,
		ordered_hash_table_info_destructor,
		ordered_hash_table_print_key,
		ordered_hash_table_print_info
	);

	for(uint32_t i = 0; i < t->capacity; i++) {
		t->table[i] = NULL;
	}

	return t;
}

void ordered_hash_table_destructor(ordered_hash_table_t* t) {
	if(t == NULL)
		return;

	for(uint32_t i = 0; i < t->capacity; i++) {
		while(t->table[i]) {
			ordered_hash_table_delete_elem(t, t->table[i]->key);
		}
	}

	free(t->table);
	free(t);
}

static void ordered_hash_table_rehash(ordered_hash_table_t** t) {
	if(t == NULL || *t == NULL)
		return;

	ordered_hash_table_t* new_t = ordered_hash_table_constructor((*t)->capacity * 2);

	for(uint32_t i = 0; i < (*t)->capacity; i++) {
		ordered_hash_table_entry_t* tmp = (*t)->table[i];
		while(tmp) {
			ordered_hash_table_insert_elem(&new_t, tmp->key, tmp->value);
			tmp = tmp->next;
		}
	}

	ordered_hash_table_destructor(*t);
	*t = new_t;
}

int ordered_hash_table_insert_elem(ordered_hash_table_t** t, const char* key, const int value) {
	if(t == NULL || *t == NULL)
		return 0;

	if(((*t)->size + 1) % (*t)->capacity == 0) {
		ordered_hash_table_rehash(t);
	}

	uint32_t hashed_key = (*t)->hash_function((*t), key, strlen(key));

	ordered_hash_table_entry_t** entry = &((*t)->table[hashed_key]);

	while(entry != NULL && *entry != NULL ) {
		if(strcmp((*entry)->key, key) == 0) { // Item already inserted
			return 0;
		}

		entry = &(*entry)->next;
	}
	
	(*entry) = (ordered_hash_table_entry_t*)malloc(sizeof(ordered_hash_table_entry_t));
	(*entry)->key = strdup(key);
	(*entry)->value = value;
	(*entry)->next = NULL;
	(*t)->size++;
	
	(*entry)->heap_index = heap_insert_node((*t)->ordered_data, &(*entry)->value, *entry);

	return 1;
}

ordered_hash_table_entry_t* ordered_hash_table_find_elem(ordered_hash_table_t* t, const char* key) {
	if(t == NULL)
		return nullptr;

	uint32_t uikey = t->hash_function(t, key, strlen(key));
	ordered_hash_table_entry_t* entry = t->table[uikey];
	while(entry != NULL && strcmp(entry->key, key) != 0) {
		entry = entry->next;
	}

	if(entry == NULL)
		return entry;

	return entry;
}

ordered_hash_table_entry_list_t** bst_get_top_n_values(bst_node_t* current,
													   ordered_hash_table_entry_list_t** top_n_current, int* N)
{
	if (current == NULL || N <= 0)
		return top_n_current;

	ordered_hash_table_entry_list_t** n_top_n_current = bst_get_top_n_values(current->right, top_n_current, N);
	
	(*n_top_n_current) = (ordered_hash_table_entry_list_t*)malloc(sizeof(ordered_hash_table_entry_list_t));
	(*n_top_n_current)->entry = (ordered_hash_table_entry_t*)current->info;
	(*n_top_n_current)->next = NULL;
	--(*N);
	
	return bst_get_top_n_values(current->left, &(*n_top_n_current)->next, N);
}

ordered_hash_table_entry_t* ordered_hash_table_get_top_n_values(ordered_hash_table_t* t, int N) {
	if (t == NULL)
		return NULL;
	
	ordered_hash_table_entry_t* top_n = (ordered_hash_table_entry_t*)malloc(N*sizeof(ordered_hash_table_entry_t));
	heap_node_t* h_nodes = heap_top_n(t->ordered_data, N);
	for (size_t i = 0; (int)i < N; ++i)
		memcpy(&top_n[i], h_nodes[i].info, sizeof(ordered_hash_table_entry_t));
	
	return top_n;
}

void ordered_hash_table_destroy_entry_list(ordered_hash_table_entry_list_t* t) {
	for (ordered_hash_table_entry_list_t* i = t; i != NULL;) {
		ordered_hash_table_entry_list_t* tmp = i;
		i = i->next;
		delete tmp;
	}
}

int ordered_hash_table_update_elem(ordered_hash_table_t* t, const char* key, const int new_value) {
	uint32_t hashed_key = t->hash_function(t, key, strlen(key));

	ordered_hash_table_entry_t** entry = &(t->table[hashed_key]);

	while(*entry != NULL ) {
		if(strcmp((*entry)->key, key) == 0) { // Item already inserted, update it
			(*entry)->value = new_value;
			return 1;
		}
	}

	return 0;
}

void ordered_hash_table_delete_elem(ordered_hash_table_t* t, const char* key) {
	if(t == NULL)
		return;

	uint32_t uikey = t->hash_function(t, key, strlen(key));
	ordered_hash_table_entry_t** entry = &(t->table[uikey]);
	while(entry != NULL && *entry != NULL && strcmp((*entry)->key, key) != 0) {
		entry = &(*entry)->next;
	}

	if(*entry == NULL)
		return;

	heap_delete_node(t->ordered_data, (*entry)->heap_index);
	
	free((*entry)->key);

	ordered_hash_table_entry_t* tmp = *entry;
	*entry = (*entry)->next;
	free(tmp);
	t->size--;
}

long ordered_hash_table_size(ordered_hash_table_t* t) {
	return t->size;
}

void ordered_hash_table_print(ordered_hash_table_t* t) {
	if(t == NULL)
		return;

	for(uint32_t i = 0; i < t->capacity; i++) {
		ordered_hash_table_entry_t* tmp = t->table[i];
		while(tmp) {
			printf("(%s, %d)\n", tmp->key, tmp->value);
			tmp = tmp->next;
		}
	}
}

int ordered_hash_table_compare_data(const void* lhs, const void* rhs) {
	const int v_lhs = *(const int *)lhs;
	const int v_rhs = *(const int *)rhs;
	if (v_lhs == v_rhs)
		return 0;
	
	return v_lhs < v_rhs ? -1 : 1;
}

void ordered_hash_table_key_destructor(void* key) {
	(void)key; // will be destroyed by ordered_hash_table_destructor
}

void ordered_hash_table_info_destructor(void* entry) {
	(void)entry; // will be destroyed by ordered_hash_table_destructor
}

void ordered_hash_table_print_key(const void* key) {
	printf("%d", *(const int*)key);
}

void ordered_hash_table_print_info(const void* entry) {
	const ordered_hash_table_entry_t* uentry = (const ordered_hash_table_entry_t*)entry;
	printf("%s", uentry->key);
}