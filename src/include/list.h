#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

#define LIST_INITIAL_SIZE 1024

typedef struct list_node_t {
	list_node_t* next;
	list_node_t* previous;
	void* data;
} list_node_t;

typedef struct list_t {
	// fields
	size_t size;
	list_node_t* first;
	list_node_t* last;
	
	// functions
	void (*data_destructor)(void* data);
	void (*print_data)(const void* data);
} list_t;

list_t* list_constructor(
		void (*data_destructor)(void* data),
		void (*print_data)(const void* data)
);

void list_destructor(list_t* l);

int list_push_back(list_t* t, void* data);

int list_push_front(list_t* t, void* data);

void* list_pop_back(list_t* t);

void* list_pop_front(list_t* t);

void* list_peek_back(list_t* t);

void* list_peek_front(list_t* t);

#endif // LIST_H